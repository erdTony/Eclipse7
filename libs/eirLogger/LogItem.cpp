#include "LogItem.h"

#include <Uid.h>

#include "Logger.h"
Q_GLOBAL_STATIC(Logger, LOG);

DEFINE_DATAPROPS(LogItem, LogItemData)



void LogItem::ctor(void)
{
    setTimeStamp(MillisecondTime::current());
    setItemUid(Uid(Uid::V8MacMsecSeq));
}

void LogItem::dtor(void) {;}

LogItem::LogItem(const LogContext ctx, const char *msg)
{
    setContext(ctx), setMessage(msg);
// TODO    LOG->enqueue(it());
}

bool LogItem::isNull() const
{
    return getItemUid().isNull();
}

bool LogItem::isWarn() const
{
    return getContext().msgType() >= Log::WarnType;
}
