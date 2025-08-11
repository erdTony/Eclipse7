#include "LogEntry.h"


#include <QBuffer>
#include <QDateTime>
#include <QTextStream>
#include <QTextStream>

LogEntry::LogEntry() {;}

LogEntry::LogEntry(const LogLevel::Value level,
                   const AText &message)
    : mLevel(level)
    , mEntryMsec(QDateTime::currentMSecsSinceEpoch())
    , mText(message)
{
    ;
}

LogEntry::LogEntry(const LogLevel::Value level,
                   const AText &format,
                   const QVariantList &args)
    : mLevel(level)
    , mEntryMsec(QDateTime::currentMSecsSinceEpoch())
    , mText(format)
    , mArguments(args)
{
    ;
}

LogEntry::LogEntry(const LogLevel::Value level,
                   const LogCondition cond,
                   const QVariantList &args)
    : mLevel(level)
    , mEntryMsec(QDateTime::currentMSecsSinceEpoch())
    , mCondition(cond)
    , mArguments(args)
{
    ;
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
    tStream << text();
    tStream << arguments().count();
    foreach (const QVariant cVar, arguments())
        tStream << cVar.typeId() << cVar.typeName()
                << cVar.toByteArray();
    tStream << condition();

    return result;
}

void LogEntry::mport(const QByteArray &ba)
{
    Q_UNUSED(ba); // TODO LogEntry::mport()
}

/*
QDebug operator << (QDebug dbg, const LogEntry &le)
{
    dbg << le.xport(); return dbg;
}
*/


