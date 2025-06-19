#include "Logger.h"

#include <QTimer>

#include "LogContext.h"

Logger::Logger(QObject *parent)
    : QObject{parent}
    , mpInputTimer(new QTimer(this))
{
    setObjectName("Logger");
}

void Logger::enqueue(const LogItem &item)
{
    mInputQueue.enqueue(item);;
}

void Logger::initialize()
{

    handleInputQueue();
    connect(mpInputTimer, &QTimer::timeout,
            this, &Logger::handleInputQueue);
    connect(mpPollTimer, &QTimer::timeout,
            this, &Logger::poll);
    mpInputTimer->start(0);
}

void Logger::handleInputQueue()
{
    if (mInputQueue.isEmpty())  return;
    const LogItem cItem = mInputQueue.dequeue();
    const Log::MsgType cItemType = cItem.getContext().msgType();
    mTypeQueue[cItemType].enqueue(cItem);
}

void Logger::poll()
{

}
