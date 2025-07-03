#include "LogItem.h"

#include <Uid.h>

#include "Logger.h"
Q_GLOBAL_STATIC(Logger, LOG);

DEFINE_DATAPROPS(LogItem, LogItemData)



void LogItem::ctor(void)
{
    timeStamp(MillisecondTime::current());
    itemUid(Uid(Uid::V8MacMsecSeq));
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
