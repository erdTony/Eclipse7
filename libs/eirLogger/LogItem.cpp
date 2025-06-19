#include "LogItem.h"


#include "LogItem.h"

DEFINE_DATAPROPS(LogItem, LogItemData)
/*
LogItem::LogItem(const int size)
    : data(new LogItemData)
    , size_i(size)
{
    ctor();
}
*/
void LogItem::ctor(void)
{
    setTimeStamp(MillisecondTime::current());
}

void LogItem::dtor(void) {;}
