#pragma once

#include <QSharedDataPointer>

class LogItemData;

class LogItem
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
