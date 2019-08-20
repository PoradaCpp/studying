#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "task.h"


class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = nullptr);
    TableModel(const QVector<Task> &tasks, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    const QVector<Task> &getTasks() const;

public slots:
    void updateTable();
    void finishTask(int nSelectedRow);
    void resetTask(int nSelectedRow);
    void start_or_pauseTask(int nSelectedRow);
    void rowSelected(QModelIndex task_index);

signals:
    void setButtonText(QString text);

private:
    QVector<Task> m_Tasks;
};

#endif // TABLEMODEL_H
