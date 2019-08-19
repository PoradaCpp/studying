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

#ifndef TASKSWIDGET_H
#define TASKSWIDGET_H

#include "tablemodel.h"

#include <QItemSelection>
#include <QWidget>
#include <QTableView>
#include <QTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSortFilterProxyModel>
#include <QItemSelectionModel>

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE

//! [0]
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
//! [0]

#endif // TASKSWIDGET_H

