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

#include "adddialog.h"

#include <QtWidgets>

//! [0]
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
//! [0]

