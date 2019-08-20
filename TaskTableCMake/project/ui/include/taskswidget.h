#ifndef TASKSWIDGET_H
#define TASKSWIDGET_H

#include <QItemSelection>
#include <QWidget>
#include <QTableView>
#include <QTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSortFilterProxyModel>
#include <QItemSelectionModel>

#include "tablemodel.h"
#include "datamodel_export.h"

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE

class TasksWidget : public QWidget
{
    Q_OBJECT

public:
    TasksWidget(QWidget *parent = nullptr);
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);
    void addContents(QTableView *pTableView, QPushButton *pFinishTaskButton, QPushButton *pResetTaskButton,
                     QPushButton *pStartPauseButton);

public slots:
    void showAddEntryDialog();
    void addEntry(QString sName, uint32_t priority, QDateTime deadTimeDate = QDateTime());
    void editEntry();
    void removeEntry();
    void selectionProc(QModelIndex index);
    void disconnectButtons();
    void enableButtons();
    void disableButtons();
    void setStartPauseButtonText(QString text);

signals:
    void selectionChanged (const QItemSelection &selected);
    void finishTask(int nSelectedRow);
    void resetTask(int nSelectedRow);
    void startTask(int nSelectedRow);
    void start_or_pauseTask(int nSelectedRow);
    void rowSelected(QModelIndex index);

private:
    void setupTabs();

    TableModel  *m_pTableData        = nullptr;
    QHBoxLayout *m_pLayout           = nullptr;
    QTableView  *m_pTableView        = nullptr;
    QSortFilterProxyModel
                *m_pProxyModel       = nullptr;
    QItemSelectionModel
                *m_pSelectionModel   = nullptr;
    QTimer      *m_pTimer            = nullptr;
    QPushButton *m_pFinishTaskButton = nullptr;
    QPushButton *m_pResetTaskButton  = nullptr;
    QPushButton *m_pStartPauseButton = nullptr;

    int         m_nSelectedRow;
    bool        m_fButtonsEnabled    = false;

private:
    void connectButtons();
};

#endif // TASKSWIDGET_H

