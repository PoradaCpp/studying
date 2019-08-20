#include "adddialog.h"

#include <QtWidgets>

AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent)
    , m_pNameText(new QLineEdit)
    , m_pPriority(new QSpinBox)
    , m_pDeadTimeEdit(new QDateTimeEdit(QDateTime::currentDateTime()))
{
    m_pPriority->setRange(1, 5);
    m_pDeadTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
    m_pDeadTimeEdit->setDisplayFormat("dd.MM.yyyy hh:mm");

    auto nameLabel = new QLabel(tr("Name"));
    auto priorityLabel = new QLabel(tr("Priority"));
    auto deadTimeLabel = new QLabel(tr("Dead Time"));
    auto okButton = new QPushButton(tr("OK"));
    auto cancelButton = new QPushButton(tr("Cancel"));

    auto vLayout = new QVBoxLayout();
    vLayout->addWidget(nameLabel);
    vLayout->addWidget(m_pNameText);

    vLayout->addWidget(priorityLabel);
    vLayout->addWidget(m_pPriority);

    vLayout->addWidget(deadTimeLabel);
    vLayout->addWidget(m_pDeadTimeEdit);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    vLayout->addLayout(buttonLayout);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(vLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Add a Task"));
}

QString AddDialog::name() const
{
    return m_pNameText->text();
}

uint32_t AddDialog::priority() const
{
    return m_pPriority->value();
}

QDateTime AddDialog::deadTime() const
{
    return m_pDeadTimeEdit->dateTime();
}

void AddDialog::editPriority(const QString &name, uint32_t priority)
{
    m_pNameText->setReadOnly(true);
    m_pNameText->setText(name);
    m_pPriority->setValue(priority);
}

void AddDialog::editDeadTime(const QString &name, QDateTime deadTime)
{
    m_pNameText->setReadOnly(true);
    m_pNameText->setText(name);
    m_pDeadTimeEdit->setDateTime(deadTime);
}
