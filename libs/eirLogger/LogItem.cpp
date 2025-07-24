#include "LogItem.h"

#include <QDateTime>

#include "Logger.h"
Q_GLOBAL_STATIC(Logger, LOG);

DEFINE_DATAPROPS(LogItem, LogItemData)



void LogItem::ctor(void)
{
    timeStamp(QDateTime::currentDateTime().toMSecsSinceEpoch());
    itemUid(QUuid()); //Uid::V8MacMsecSeq));
}

void LogItem::dtor(void) {;}

LogItem::LogItem(const LogContext ctx, const char *msg)
{
    context(ctx), message(msg);
// TODO    LOG->enqueue(it());
}

bool LogItem::isNull() const
{
    return itemUid().isNull();
}

bool LogItem::isWarn() const
{
    return context().msgType() >= Log::WarnType;
}
