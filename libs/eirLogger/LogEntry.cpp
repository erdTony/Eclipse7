#include "LogEntry.h"


#include <QBuffer>
#include <QDateTime>
#include <QTextStream>

#include <Bytes.h>

#include "Log.h"

LogEntry::LogEntry() : mLevel(LogLevel::$nullLevel) {;}
LogEntry::LogEntry(const QByteArray &ba) { mport(ba); }
LogEntry::LogEntry(const LogLevel::Value level, const AText &message)
    : mLevel(level), mFormat(message) {;}

LogEntry::LogEntry(const LogLevel::Value level,
                   const AText &format,
                   const QVariant &arg1,
                   const QVariant &arg2,
                   const QVariant &arg3,
                   const QVariant &arg4)
    : mLevel(level)
    , mFormat(format)
    , mArguments(QVariantList() << format << arg1 << arg2 << arg3 << arg4)
{
    ;
}

LogEntry::LogEntry(const LogLevel::Value level,
                   const AText &format,
                   const QVariantList &args)
    : mLevel(level)
    , mFormat(format)
    , mArguments(args)
{
    mArguments.prepend(format);
}

LogEntry::LogEntry(const LogLevel::Value level,
                   const LogCondition cond,
                   const CText &expName,
                   const QVariant &expValue,
                   const CText &actName,
                   const QVariant &actValue)
    : mLevel(level)
    , mCondition(cond)
    , mArguments(QVariantList() << expName << expValue << actName << actValue)
{
    mArguments.prepend(cond.text());
}

bool LogEntry::isNull() const
{
    return ! mLevel.isValidLevel();
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
    tStream << format();
    tStream << condition();
    tStream << arguments().count();
    foreach (const QVariant cVar, arguments())
    {
        Bytes tVarBytes(cVar);
        tStream << cVar.typeId() << tVarBytes.base64();
    }
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
    int tCond; tStream >> tCond;
    mCondition.set(tCond);
    Count tArgCount; tStream >> tArgCount;
    tStream >> tArgCount;

    mArguments.fill(QVariant(), tArgCount);
    for (Index ix = 0; ix < Index(tArgCount); ++ix)
    {
        int tTypeId; tStream >> tTypeId;
        QByteArray tBase64; tStream >> tBase64;
        QByteArray tVarBytes = QByteArray::fromBase64(tBase64);
        QVariant tArgVar(QMetaType(tTypeId), tVarBytes.data());
        mArguments[ix] = tArgVar;
    }
}

