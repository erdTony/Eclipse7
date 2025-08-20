#include "LogItem.h"

#include <QDateTime>
#include <QDomDocument>
#include <QSqlRecord>


#include "Logger.h"
#include "LogEntry.h"
#include "LogMessage.h"

DEFINE_DATAPROPS(LogItem, LogItemData);
void LogItem::ctor(void) {;}
void LogItem::dtor(void) {;}

LogItem::LogItem(const LogMessage &lm)
{
    set(lm);
}

bool LogItem::isNull() const
{
    return logUid().isNull() || level().isNull();
}

QString LogItem::displayString() const
{
    return QString("%1%2: %3,%4 %5 %6 %7")
        /* %1 */ .arg(level().chr())
        /* %2 */ .arg(QDateTime::fromMSecsSinceEpoch(timeStamp())
                         .toString("hh:mm:ss.zzz"))
        /* %3 */ .arg(fileInfo().baseFileName()())
        /* %4 */ .arg(fileLine(), 4)
        /* %5 */ .arg(formattedMessage())
        /* %6 */ .arg(level().name()())
        /* %7 */ .arg(funcInfo().qFuncInfo())
        ;
}

QStringList LogItem::formatStringList() const
{
    QStringList result;
    // TODO
    return result;
}

QDomDocument LogItem::formatXmlDocument() const
{
    QDomDocument result;
    // TODO

    return result;
}

void LogItem::set(const LogMessage &lm)
{
    LogEntry le(lm.message().toLocal8Bit());
    timeStamp(le.entryMsec()),
    logUid(Uid(Uid::Log)),
    fileInfo(LogFileInfo(lm.fileName())),
    fileLine(lm.fileLine()),
    funcInfo(LogFuncInfo(lm.funcName())),
    format(le.format()),
    condition(le.condition()),
    values(le.arguments());
}

QString LogItem::formattedMessage() const
{
    QString result = format();
    if (condition() == LogCondition::$null)
    {
        for (int ix = 1; ix <= 9; ++ix)
        {
            QString tPercent = QString("%%%1").arg(ix);
            if (result.contains(tPercent))
                result.replace(tPercent, valueString(ix));

        }
    }
    else
    {
        result = QString("%1 [%2 (%3)] %4 [%5 (%6)] %7")
                     /* %1 */ .arg(level().name()())
                     /* %2 */ .arg(valueString(1))
                     /* %3 */ .arg(value(2).toString())
                     /* %4 */ .arg(condition().text()())
                     /* %5 */ .arg(valueString(3))
                     /* %6 */ .arg(value(4).toString())
                     /* %7 */ .arg(format())
            ;
    }
    return result;
}

bool LogItem::isValidValueIndex(const qsizetype ix) const
{
    return ix >= 0 && ix < values().count();
}

QVariant LogItem::value(const qsizetype ix) const
{
    return isValidValueIndex(ix) ? values().at(ix) : QVariant();
}

QString LogItem::valueString(const qsizetype ix) const
{
    return value(ix).toString();
}

