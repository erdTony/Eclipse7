#include "LogItem.h"

#include <QDateTime>

#include <Uid.h>

#include "Logger.h"
Q_GLOBAL_STATIC(Logger, LOG);

DEFINE_DATAPROPS(LogItem, LogItemData);



void LogItem::ctor(void)
{
    timeStamp(QDateTime::currentDateTime().toMSecsSinceEpoch());
}

void LogItem::dtor(void) {;}

LogItem::LogItem(const LogEntry &le)
{
    set(le);
}

bool LogItem::isNull() const
{
    return logUid().isNull();
}

bool LogItem::isWarn() const
{
    return false; // TODO
}

QString LogItem::formattedMessage() const
{
    return QString(); // TODO
}

void LogItem::set(const LogEntry &le)
{
    level(le.level()),
        timeStamp(le.logMsec()),
        logUid(le.logUid()),
        logEntry(le),
        format(le.text()),
        cond(le.condition()),
        values(le.arguments()),
        expectedName(le.expectedName()),
        actualName(le.actualName()),
        expectedValue(le.argument(0)),
        actualValue(le.argument(1));


}
