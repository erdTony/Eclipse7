#include "LogItem.h"

#include <utility>

class LogItemData : public QSharedData
{
public:

};

LogItem::LogItem()
    : data(new LogItemData)
{}

LogItem::LogItem(const LogItem &rhs)
    : data{rhs.data}
{}

LogItem::LogItem(LogItem &&rhs)
    : data{std::move(rhs.data)}
{}

LogItem &LogItem::operator=(const LogItem &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

LogItem &LogItem::operator=(LogItem &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

LogItem::~LogItem() {}
