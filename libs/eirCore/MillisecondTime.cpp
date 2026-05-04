#include "MillisecondTime.h"

const QDateTime MillisecondTime::smBaseDateTime(QDateTime::currentDateTime());
const MillisecondTime MillisecondTime::smBaseMST(smBaseDateTime);
const MillisecondTime MillisecondTime::smNullMST(INT64_MIN);

MillisecondTime::MillisecondTime(void)
    : mEpochMS(smNullMST)
{
}

MillisecondTime::MillisecondTime(Milliseconds ems)
    : mEpochMS(ems)
{
}

MillisecondTime::MillisecondTime(const QDateTime & dt)
    : mEpochMS(dt.isValid() ? dt.toMSecsSinceEpoch() : INT64_MIN)
{
}

MillisecondTime MillisecondTime::current(void)
{
    return MillisecondTime(QDateTime::currentMSecsSinceEpoch());
}

MillisecondTime MillisecondTime::fromIso(const QString & isoDateTime)
{
    return MillisecondTime(QDateTime::fromString(isoDateTime, Qt::ISODate));
}

MillisecondTime MillisecondTime::fromString(const QString & dateTime)
{
    qint64 i64 = dateTime.toLongLong();
    return MillisecondTime((i64 > 3000)
                           ? QDateTime::fromMSecsSinceEpoch(i64)
                           : QDateTime::fromString(dateTime, Qt::ISODate));
}

bool MillisecondTime::isValid(void) const
{
    return toDateTime().isValid();
}

bool MillisecondTime::isNull(void) const
{
    return smNullMST == mEpochMS;
}

bool MillisecondTime::isBaseNull(void) const
{
    return smNullMST == smBaseMST;
}

MillisecondTime::operator Milliseconds(void) const
{
    return mEpochMS;
}

MillisecondTime & MillisecondTime::operator += (const MillisecondTime d)
{
    mEpochMS += d;
    return *this;
}

MillisecondTime & MillisecondTime::operator -= (const MillisecondTime d)
{
    mEpochMS -= d;
    return *this;
}

void MillisecondTime::set(const MillisecondTime other)
{
    mEpochMS = other.mEpochMS;
}

void MillisecondTime::nullify(void)
{
    mEpochMS = smNullMST;
}

Milliseconds MillisecondTime::base(void)
{
    return smBaseMST;
}

MillisecondTime MillisecondTime::null(void)
{
    return smNullMST;
}

MillisecondTime MillisecondTime::delta(MillisecondTime ems) const
{
    return MillisecondTime(ems - mEpochMS);
}

MillisecondTime MillisecondTime::deltaBase(MillisecondTime ems)
{
    return MillisecondTime(ems - smBaseMST);
}

QDateTime MillisecondTime::toDateTime(void) const
{
    return QDateTime::fromMSecsSinceEpoch(mEpochMS);
}

QString MillisecondTime::toSecString(const Milliseconds roll) const
{
    QString result("###????");
    if (mEpochMS == 0)
        result = "-0-";
    else if (mEpochMS >= roll)
        result = QString("%1.%2 sec").arg(mEpochMS / 1000).arg((mEpochMS % 1000) / 100, 1, 10);
    else
        result = QString("%1 ms").arg(mEpochMS, 4);
    return result;

}

QString MillisecondTime::toString(const QString & format) const
{
    return toDateTime().toString(format.isEmpty()
                                 ? "yyyy/MM/dd hh:mm:ss.zzz"
                                 : format);
}

QString MillisecondTime::timeString(const bool msec) const
{
    return toString("hh:mm:ss%1").arg(msec ? ".zzz" : "");
}

QString MillisecondTime::baseString(const QString & format)
{
    return QDateTime::fromMSecsSinceEpoch(smBaseMST)
        .toString(format.isEmpty() ? "yyyy/MM/dd hh:mm:ss.zzz" : format);
}
