#include "StructTM.h"

#include <QDate>
#include <QTime>

StructTM::StructTM(const bool now)
{
    if (now)
        set(QDateTime::currentDateTimeUtc());
    else
        clear();
}

StructTM::StructTM(const QDateTime dttm)
{
    set(dttm);
}

time_t StructTM::timeT() const
{
    struct tm tSTM;
    memcpy(&tSTM, &mSTM, sizeof(tSTM));
    return mktime(&tSTM);
}

void StructTM::clear()
{
    mBytes = QByteArray((const char *)(&mSTM), sizeof(mSTM));
    mBytes.fill(0);
}

void StructTM::set(const QDateTime dttm)
{
    clear();
    QDate tDate = dttm.date();
    QTime tTime = dttm.time();
    mSTM.tm_year = tDate.year(),
        mSTM.tm_mon = tDate.month(),
        mSTM.tm_mday = tDate.day();
    mSTM.tm_hour = tTime.hour(),
        mSTM.tm_min = tTime.minute(),
        mSTM.tm_sec = tTime.second(),
        mSTM.tm_isdst = dttm.isDaylightTime();
}
