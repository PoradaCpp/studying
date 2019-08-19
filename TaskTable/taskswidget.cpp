#include "taskswidget.h"
#include "adddialog.h"

#include <QtWidgets>

TasksWidget::TasksWidget(QWidget *parent)
    : QWidget(parent)
    , m_pTableData(new TableModel(this))
    , m_pLayout(new QHBoxLayout(this))
    , m_pProxyModel(new QSortFilterProxyModel(this))
{}

void TasksWidget::showAddEntryDialog()
{
    AddDialog aDialog;

    if (aDialog.exec())
    {
        addEntry(aDialog.name(), aDialog.priority(), aDialog.deadTime());
    }
}

void TasksWidget::addEntry(QString sName, uint32_t priority, QDateTime deadTimeDate)
{
    if (!m_pTableData->getTasks().contains({ sName, priority, deadTimeDate }))
    {
        m_pTableData->insertRows(0, 1, QModelIndex());

        QModelIndex index = m_pTableData->index(0, 0, QModelIndex());
        m_pTableData->setData(index, sName, Qt::EditRole);

        index = m_pTableData->index(0, 1, QModelIndex());
        m_pTableData->setData(index, priority, Qt::EditRole);

        index = m_pTableData->index(0, 4, QModelIndex());
        m_pTableData->setData(index, deadTimeDate, Qt::EditRole);

        if(!m_pTimer)
        {
            m_pTimer = new QTimer(this);
            connect(m_pTimer, &QTimer::timeout, m_pTableData, &TableModel::updateTable);
            m_pTimer->start(1000);
        }
    }
    else
    {
        QMessageBox::information(this, tr("Duplicate Name"),
            tr("The name \"%1\" already exists.").arg(sName));
    }
}

void TasksWidget::editEntry()
{
    m_pSelectionModel = m_pTableView->selectionModel();

    const QModelIndexList indexes = m_pSelectionModel->selectedRows();
    QString name;
    uint32_t priority(0);
    QDateTime deadTime;
    int row = -1;

    for (const QModelIndex &index : indexes)
    {
        row = m_pProxyModel->mapToSource(index).row();
        QModelIndex nameIndex = m_pTableData->index(row, 0, QModelIndex());
        QVariant varName = m_pTableData->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex priorityIndex = m_pTableData->index(row, 1, QModelIndex());
        QVariant varPrior = m_pTableData->data(priorityIndex, Qt::DisplayRole);
        priority = varPrior.toUInt();

        QModelIndex deadTimeIndex = m_pTableData->index(row, 4, QModelIndex());
        QVariant varDeadTime = m_pTableData->data(deadTimeIndex, Qt::DisplayRole);
        deadTime = varDeadTime.toDateTime();
    }

    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edit a Task"));
    aDialog.editPriority(name, priority);
    aDialog.editDeadTime(name, deadTime);

    if (aDialog.exec())
    {
        const uint32_t newPriority = aDialog.priority();
        if (newPriority != priority)
        {
            const QModelIndex index = m_pTableData->index(row, 1, QModelIndex());
            m_pTableData->setData(index, newPriority, Qt::EditRole);
        }

        const QDateTime newDeadTime = aDialog.deadTime();
        if (newDeadTime != deadTime)
        {
            const QModelIndex index = m_pTableData->index(row, 4, QModelIndex());
            m_pTableData->setData(index, newDeadTime, Qt::EditRole);
        }
    }
}

void TasksWidget::removeEntry()
{
    m_pSelectionModel = m_pTableView->selectionModel();

    const QModelIndexList indexes = m_pSelectionModel->selectedRows();

    for (QModelIndex index : indexes)
    {
        int row = m_pProxyModel->mapToSource(index).row();
        m_pTableData->removeRows(row, 1, QModelIndex());
    }

    if(!m_pTableData->rowCount(QModelIndex()))
    {
        if(m_fButtonsEnabled)
        {
            disableButtons();
            m_fButtonsEnabled = false;
        }
    }
}

void TasksWidget::selectionProc(QModelIndex index)
{
    if(!m_fButtonsEnabled)
    {
        enableButtons();
        m_fButtonsEnabled = true;
    }
    m_nSelectedRow = m_pProxyModel->mapToSource(index).row();
}

void TasksWidget::disconnectButtons()
{
    m_pFinishTaskButton->disconnect();
    m_pResetTaskButton->disconnect();
    m_pStartPauseButton->disconnect();
}

void TasksWidget::enableButtons()
{
    m_pFinishTaskButton->setEnabled(true);
    m_pResetTaskButton->setEnabled(true);
    m_pStartPauseButton->setEnabled(true);
}

void TasksWidget::disableButtons()
{
    m_pFinishTaskButton->setEnabled(false);
    m_pResetTaskButton->setEnabled(false);
    m_pStartPauseButton->setEnabled(false);
}

void TasksWidget::setStartPauseButtonText(QString text)
{
    m_pStartPauseButton->setText(text);
}

void TasksWidget::setupTabs()
{
    m_pProxyModel->setSourceModel(m_pTableData);
    m_pProxyModel->setFilterKeyColumn(0);

    m_pTableView->setModel(m_pProxyModel);
    m_pTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableView->horizontalHeader()->setStretchLastSection(true);
    m_pTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_pTableView->verticalHeader()->hide();
    m_pTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableView->setSortingEnabled(true);

    connect(m_pTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &TasksWidget::selectionChanged);
    connect(m_pTableView, &QTableView::clicked, this, &TasksWidget::selectionProc);

    connect(this, &TasksWidget::finishTask, m_pTableData, &TableModel::finishTask);
    connect(this, &TasksWidget::resetTask, m_pTableData, &TableModel::resetTask);
    connect(this, &TasksWidget::start_or_pauseTask, m_pTableData, &TableModel::start_or_pauseTask);
    connect(m_pTableView, &QTableView::clicked, m_pTableData, &TableModel::rowSelected);
    connect(m_pTableData, &TableModel::setButtonText, this, &TasksWidget::setStartPauseButtonText);
    connectButtons();

    m_pLayout->addWidget(m_pTableView);
}

void TasksWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QVector<Task> tasks;
    QDataStream in(&file);
    in >> tasks;

    if (tasks.isEmpty())
    {
        QMessageBox::information(this, tr("No contacts in file"),
                                 tr("The file you are attempting to open contains no contacts."));
    }
    else
    {
        if(m_pTableData)
        {
            delete m_pTableData;
        }
        if(m_pLayout)
        {
            delete m_pLayout;
        }
        m_pLayout = new QHBoxLayout(this);
        m_pTableData = new TableModel(tasks, this);
        disconnectButtons();
        m_pTableView->disconnect();
        setupTabs();

        if(!m_pTimer)
        {
            m_pTimer = new QTimer(this);
            connect(m_pTimer, &QTimer::timeout, m_pTableData, &TableModel::updateTable);
            m_pTimer->start(1000);
        }
    }
}

void TasksWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }
    QDataStream out(&file);
    out << m_pTableData->getTasks();
}

void TasksWidget::addContents(QTableView *pTableView, QPushButton *pFinishTaskButton, QPushButton *pResetTaskButton,
                              QPushButton *pStartPauseButton)
{
    m_pTableView        = pTableView;
    m_pFinishTaskButton = pFinishTaskButton;
    m_pResetTaskButton  = pResetTaskButton;
    m_pStartPauseButton = pStartPauseButton;

    disableButtons();
    setupTabs();
}

void TasksWidget::connectButtons()
{
    connect(m_pFinishTaskButton, &QPushButton::clicked, m_pTableData, [this]
    {
        emit finishTask(m_nSelectedRow);
    });

    connect(m_pResetTaskButton, &QPushButton::clicked, this, [this]
    {
        emit resetTask(m_nSelectedRow);
    });

    connect(m_pStartPauseButton, &QPushButton::clicked, this, [this]
    {
        emit start_or_pauseTask(m_nSelectedRow);
    });
}
