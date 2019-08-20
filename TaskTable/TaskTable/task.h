#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDataStream>
#include <QDateTime>

#include "duration.h"

class Task
{
public:
    enum class TaskState
    {
        RESETED  = 0,
        STARTED  = 1,
        PAUSED   = 2,
        FINISHED = 3
    };

    Task();
    Task(QString sName, uint32_t priority, QDateTime nDeadTimeDate = QDateTime());

    friend QDataStream &operator<<(QDataStream &stream, const Task &task);
    friend QDataStream &operator>>(QDataStream &stream, Task &task);

    void setName(QString sName);
    void setState(TaskState state);
    void setPriority(uint32_t  priority);
    void setDeadTimeDate(QDateTime deadTimeDate);
    void addSpentTime();

    QString getName() const;
    QString getState() const;
    uint32_t  getPriority() const;
    QDateTime getCreationTimeDate() const;
    QDateTime getDeadTimeDate() const;
    QString getSpentTime() const;

    bool operator==(const Task &other) const;

private:
    QString   m_sName;
    int       m_nState;
    uint32_t  m_Priority;
    QDateTime m_CreationDate;
    QDateTime m_DeadTimeDate;
    Duration  m_SpentTime;
};

#endif // TASK_H
