#include "LogEntry.h"


#include <QBuffer>
#include <QDateTime>
#include <QTextStream>


#include "Log.h"

LogEntry::LogEntry()
    : mLevel(LogLevel::$nullLevel)
    , mLogMsec(0)
    , mLogUid(Uid(true))
{;}

LogEntry::LogEntry(const QByteArray &ba)
{
    mport(ba);
}

LogEntry::LogEntry(const LogLevel::Value level,
                   const AText &message)
    : mLevel(level)
    , mLogMsec(QDateTime::currentMSecsSinceEpoch())
    , mLogUid(Uid(Uid::Log))
    , mText(message)
{
    ;
}

LogEntry::LogEntry(const LogLevel::Value level,
                   const AText &format,
                   const QVariant &arg1,
                   const QVariant &arg2,
                   const QVariant &arg3,
                   const QVariant &arg4)
    : mLevel(level)
    , mLogMsec(QDateTime::currentMSecsSinceEpoch())
    , mLogUid(Uid(Uid::Log))
    , mText(format)
    , mArguments(QVariantList() << arg1 << arg2 << arg3 << arg4)
{
    ;
}

LogEntry::LogEntry(const LogLevel::Value level,
                   const AText &format,
                   const QVariantList &args)
    : mLevel(level)
    , mLogMsec(QDateTime::currentMSecsSinceEpoch())
    , mLogUid(Uid(Uid::Log))
    , mText(format)
    , mArguments(args)
{
    ;
}

LogEntry::LogEntry(const LogLevel::Value level,
                   const LogCondition cond,
                   const CText &expName,
                   const QVariant &expValue,
                   const CText &actName,
                   const QVariant &actValue)
    : mLevel(level)
    , mLogMsec(QDateTime::currentMSecsSinceEpoch())
    , mLogUid(Uid(Uid::Log))
    , mCondition(cond)
    , mExpectedName(expName)
    , mActualName(actName)
    , mArguments(QVariantList() << expValue << actValue)
{
    ;
}

bool LogEntry::isNull() const
{
    if (mLevel.isValidLevel())          return true;
    if (0 == mLogMsec)                return true;
    if (mLogUid.isNull())             return true;
    return false;
}

QVariant LogEntry::argument(const Index ix) const
{
    return (ix >= 0 && ix < arguments().count())
               ? arguments().value(ix) : QVariant();
}

QByteArray LogEntry::xport() const
{
    QByteArray result;
    QBuffer tBuffer(&result);
    tBuffer.open(QIODevice::WriteOnly);
    QTextStream tStream(&tBuffer);

    tStream << level().value();
    tStream << mLogMsec;
    tStream << text();
    tStream << condition();
    tStream << expectedName();
    tStream << actualName();
    tStream << arguments().count();
    foreach (const QVariant cVar, arguments())
        tStream << cVar.typeId() << cVar.typeName()
                << cVar.toByteArray();
    tBuffer.close();
    return result;
}

void LogEntry::mport(const QByteArray &ba)
{
    QByteArray tBytes(ba);
    QBuffer tBuffer(&tBytes);
    tBuffer.open(QIODevice::ReadOnly);
    QTextStream tStream(&tBuffer);
    \
    int tLevel; tStream >> tLevel;
    mLevel.set(tLevel);
    qint64 tMsec; tStream >> tMsec;
    mLogMsec = tMsec;
    int tCond; tStream >> tCond;
    mCondition.set(tCond);

    tStream >> mExpectedName;
    tStream >> mActualName;

    Count tArgCount; tStream >> tArgCount;
    tStream >> tArgCount;
    mArguments.fill(QVariant(), tArgCount);
    for (Index ix = 0; ix < Index(tArgCount); ++ix)
    {
        int tTypeId; tStream >> tTypeId;
        CText tTypeName; tStream >> tTypeName; Q_UNUSED(tTypeName);
        QByteArray tBA; tStream >> tBA;
        QVariant tArgVar(tBA);
        tArgVar.convert(QMetaType(tTypeId));
        mArguments[ix] = tArgVar;
    }
}

/*
QDebug operator << (QDebug dbg, const LogEntry &le)
{
    dbg << le.xport(); return dbg;
}
*/


