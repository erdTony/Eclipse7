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
    LOG->enqueue(*this);
}
