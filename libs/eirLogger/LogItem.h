#pragma once
#include "eirlogger.h"

#include <QSharedDataPointer>

class LogItemData;

class EIRLOGGER_EXPORT LogItem
{


    // built in
public:
    LogItem();
    LogItem(const LogItem &);
    LogItem(LogItem &&);
    LogItem &operator=(const LogItem &);
    LogItem &operator=(LogItem &&);
    ~LogItem();

private:
    QSharedDataPointer<LogItemData> data;
};
