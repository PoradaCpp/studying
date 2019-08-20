#include "duration.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

Duration::Duration(qint64 nSecs /* = 0*/)
    : m_nSpentTime(nSecs)
{}

void Duration::addDurTime(qint64 nSecs)
{
    m_nSpentTime += nSecs;
}

void Duration::resetDurTime()
{
    m_nSpentTime = 0;
}

QString Duration::getDurationTime() const
{
    uint64_t nSeconds = m_nSpentTime % SECS_IN_MIN;
    uint64_t nMinutes = m_nSpentTime / SECS_IN_MIN;
    uint64_t nHours = nMinutes / MINS_IN_HOUR;
    nMinutes = nMinutes % MINS_IN_HOUR;
    uint64_t nDays = nHours / HOURS_IN_DAY;
    nHours = nHours % HOURS_IN_DAY;
    uint64_t nMonths = nDays / DAYS_IN_MONTH;
    nDays = nDays % DAYS_IN_MONTH;
    uint64_t nYears = nMonths / MONTHS_IN_YEAR;
    nMonths = nMonths % MONTHS_IN_YEAR;

    std::stringstream DateStringStream;
    DateStringStream << std::setw(2) << std::setfill('0') << std::to_string(nYears)   << "."
                     << std::setw(2) << std::setfill('0') << std::to_string(nMonths)  << "."
                     << std::setw(2) << std::setfill('0') << std::to_string(nDays)    << " "
                     << std::setw(2) << std::setfill('0') << std::to_string(nHours)   << ":"
                     << std::setw(2) << std::setfill('0') << std::to_string(nMinutes) << ":"
                     << std::setw(2) << std::setfill('0') << std::to_string(nSeconds);

    QString QDateString = QString::fromStdString(DateStringStream.str());
    return QDateString;
}

qint64 Duration::getSpentSecs() const
{
    return m_nSpentTime;
}

QDataStream &operator<<(QDataStream &stream, const Duration &duration)
{
    return stream << duration.m_nSpentTime;
}

QDataStream &operator>>(QDataStream &stream, Duration &duration)
{
    return stream >> duration.m_nSpentTime;
}
