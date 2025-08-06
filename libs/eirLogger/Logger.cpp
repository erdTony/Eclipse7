#include "Logger.h"

#include <QTimer>
#include <QUrl>


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

bool Logger::addOutput(const QUrl &url)
{
// TODO    const Url::Type cType = url.type();
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
}

void Logger::poll()
{

}
