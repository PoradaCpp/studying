#include "task.h"

#include <QDebug>

Task::Task()
    : m_sName("")
    , m_nState(static_cast<int>(TaskState::RESETED))
    , m_Priority(1)
    , m_CreationDate(QDateTime::currentDateTime())
    , m_DeadTimeDate(QDateTime())
    , m_SpentTime()
{}

Task::Task(QString sName, uint32_t priority, QDateTime nDeadTimeDate)
    : m_sName(sName)
    , m_nState(static_cast<int>(TaskState::RESETED))
    , m_Priority(priority)
    , m_CreationDate(QDateTime::currentDateTime())
    , m_DeadTimeDate(nDeadTimeDate)
    , m_SpentTime()
{}

void Task::setName(QString sName)
{
    m_sName = sName;
}

void Task::setState(TaskState state)
{
    if(TaskState::RESETED == state)
    {
        m_SpentTime.resetDurTime();
    }
    m_nState = static_cast<int>(state);
}

void Task::setPriority(uint32_t priority)
{
    m_Priority = priority;
}

void Task::setDeadTimeDate(QDateTime deadTimeDate)
{
    m_DeadTimeDate = deadTimeDate;
}

void Task::addSpentTime()
{
    if(TaskState::STARTED == static_cast<TaskState>(m_nState))
    {
        m_SpentTime.addDurTime(1);
    }
}

QString Task::getName() const
{
    return m_sName;
}

QString Task::getState() const
{
    switch (static_cast<TaskState>(m_nState))
    {
    case TaskState::RESETED:
    return "RESETED";

    case TaskState::STARTED:
    return "STARTED";

    case TaskState::PAUSED:
    return "PAUSED";

    case TaskState::FINISHED:
    return "FINISHED";
    }
    return QString();
}

uint32_t Task::getPriority() const
{
    return m_Priority;
}

QDateTime Task::getCreationTimeDate() const
{
    return m_CreationDate;
}

QDateTime Task::getDeadTimeDate() const
{
    return m_DeadTimeDate;
}

QString Task::getSpentTime() const
{
    return m_SpentTime.getDurationTime();
}

bool Task::operator==(const Task &other) const
{
    return m_sName == other.m_sName;
}

DATAMODEL_EXPORT QDataStream &operator<<(QDataStream &stream, const Task &task)
{
    return stream << task.m_sName
                  << (Task::TaskState::STARTED == static_cast<Task::TaskState>(task.m_nState)
                      ? static_cast<int>(Task::TaskState::PAUSED)
                      : task.m_nState)
                  << task.m_Priority << task.m_CreationDate
                  << task.m_DeadTimeDate << task.m_SpentTime;
}

DATAMODEL_EXPORT QDataStream &operator>>(QDataStream &stream, Task &task)
{
    return stream >> task.m_sName >> task.m_nState >> task.m_Priority >> task.m_CreationDate
                  >> task.m_DeadTimeDate >> task.m_SpentTime;
}
