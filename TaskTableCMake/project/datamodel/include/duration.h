#ifndef DURATION_H
#define DURATION_H

#include <QDateTime>
#include <QDataStream>

#include "datamodel_export.h"

class DATAMODEL_EXPORT Duration
{
public:
    Duration(qint64 nSecs = 0);

    void addDurTime(qint64 nSecs);
    void resetDurTime();
    QString getDurationTime() const;
    qint64 getSpentSecs() const;

    friend QDataStream &operator<<(QDataStream &stream, const Duration &duration);
    friend QDataStream &operator>>(QDataStream &stream, Duration &duration);

private:
    static const qint64 SECS_IN_MIN = 60;
    static const qint64 MINS_IN_HOUR = 60;
    static const qint64 HOURS_IN_DAY = 24;
    static const qint64 DAYS_IN_MONTH = 30;
    static const qint64 MONTHS_IN_YEAR = 12;

    qint64 m_nSpentTime = 0;
};

#endif // DURATION_H
