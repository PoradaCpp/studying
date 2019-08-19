/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "tablemodel.h"

#include <QDebug>

//! [0]
TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{}

TableModel::TableModel(const QVector<Task> &tasks, QObject *parent)
    : QAbstractTableModel(parent)
    , m_Tasks(tasks)
{}
//! [0]

//! [1]
int TableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_Tasks.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 6;
}
//! [1]

//! [2]
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= m_Tasks.size() || index.row() < 0)
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        const auto &task = m_Tasks.at(index.row());

        switch (index.column())
        {
            case 0:
                return task.getName();
            case 1:
                return task.getPriority();
            case 2:
                return task.getCreationTimeDate();
            case 3:
                return task.getSpentTime();
            case 4:
                return task.getDeadTimeDate();
            case 5:
                return task.getState();
            default:
                break;
        }
    }
    return QVariant();
}
//! [2]

//! [3]
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return tr("Name");
            case 1:
                return tr("Priority");
            case 2:
                return tr("Creation Date");
            case 3:
                return tr("Spent Time");
            case 4:
                return tr("Dead Time");
            case 5:
                return tr("Current State");
            default:
                break;
        }
    }
    return QVariant();
}
//! [3]

//! [4]
bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
    {
       m_Tasks.insert(position, {});
    }
    endInsertRows();
    return true;
}
//! [4]

//! [5]
bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
    {
        m_Tasks.removeAt(position);
    }
    endRemoveRows();
    return true;
}
//! [5]

//! [6]
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        const int row = index.row();
        auto task = m_Tasks.value(row);

        switch (index.column())
        {
            case 0:
                task.setName(value.toString());
                break;
            case 1:
                task.setPriority(value.toUInt());
                break;
            case 4:
                task.setDeadTimeDate(value.toDateTime());
            break;
            default:
                return false;
        }
        m_Tasks.replace(row, task);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

        return true;
    }
    return false;
}
//! [6]

//! [7]
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
//! [7]

//! [8]
const QVector<Task> &TableModel::getTasks() const
{
    return m_Tasks;
}

void TableModel::updateTable()
{
    for (Task &task : m_Tasks)
    {
        task.addSpentTime();
    }
    QModelIndex spentTimeUpIndex = index(0, 3, QModelIndex());
    QModelIndex spentTimeBottomIndex = index(rowCount(QModelIndex()) - 1, 3, QModelIndex());

    emit dataChanged(spentTimeUpIndex, spentTimeBottomIndex, {Qt::DisplayRole, Qt::EditRole});
}

void TableModel::finishTask(int nSelectedRow)
{
    if(nSelectedRow < m_Tasks.size() && nSelectedRow >= 0)
    {
        m_Tasks[nSelectedRow].setState(Task::TaskState::FINISHED);

        QModelIndex stateIndex = index(nSelectedRow, 5, QModelIndex());
        emit dataChanged(stateIndex, stateIndex, {Qt::DisplayRole, Qt::EditRole});
        emit setButtonText("Start task");
    }
}

void TableModel::resetTask(int nSelectedRow)
{
    if(nSelectedRow < m_Tasks.size() && nSelectedRow >= 0)
    {
        m_Tasks[nSelectedRow].setState(Task::TaskState::RESETED);

        QModelIndex stateIndex = index(nSelectedRow, 5, QModelIndex());
        emit dataChanged(stateIndex, stateIndex, {Qt::DisplayRole, Qt::EditRole});
        emit setButtonText("Start task");
    }
}

void TableModel::start_or_pauseTask(int nSelectedRow)
{
    if(nSelectedRow < m_Tasks.size() && nSelectedRow >= 0)
    {
        Task &task = m_Tasks[nSelectedRow];
        QString text;

        if("STARTED" == task.getState())
        {
            task.setState(Task::TaskState::PAUSED);
            text = "Start task";
        }
        else
        {
            task.setState(Task::TaskState::STARTED);
            text = "Pause task";
        }
        QModelIndex stateIndex = index(nSelectedRow, 5, QModelIndex());
        emit dataChanged(stateIndex, stateIndex, {Qt::DisplayRole, Qt::EditRole});
        emit setButtonText(text);
    }
}

void TableModel::rowSelected(QModelIndex task_index)
{
    if(task_index.isValid())
    {
        const int row = task_index.row();

        emit setButtonText("STARTED" == m_Tasks[row].getState() ? "Pause task" : "Start task");
    }
}
//! [8]
