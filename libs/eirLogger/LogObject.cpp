#include "LogObject.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QTimer>

#include <CTextList.h>

#include "LogOutput.h"
#include "LogEntry.h"
#include "LogLevel.h"

Log::Log() : QObject{qApp}
{
    setObjectName("Log");
    QTimer::singleShot(0, this, &Log::start);
}

Log::~Log()
{
    emit destructing();
}

void Log::start()
{
    Q_ASSERT(connect(this, &Log::starting,
                     this, &Log::hookQtMsg));
    Q_ASSERT(connect(this, &Log::destructing,
                     this, &Log::unhookQtMsg));

    emit starting();
}

void Log::hookQtMsg()
{
    static CTextList sPatternList
        = CTextList()
          << "TimeString=%{time DyyyyMMddThhmmsszzz}"
          << "Function=%{function}"
          << "Message=%{message}"
#ifndef Q_OS_WINDOWS
          << "BackTrace=%{backtrace}"
#endif
        ;
    const CText cCTx = sPatternList.join('~');
    const QString cPattern(cCTx);
    qSetMessagePattern(cPattern);
    mOldHandler = qInstallMessageHandler(logMessageHandler);
}

void Log::add(LogOutput *out)
{
    if (mOutputListLock.tryLockForWrite(100))
    {
        out->setParent(this);
        mOutputList.append(out);
        emit addedOutput(out);
    }
    else
    {
        QString warn = QString("%1 LogMessage output lock failed: %2")
            .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs))
            .arg(out->name()());
        emit warning(warn);

    }
}

void Log::enqueueMessage(const LogMessage &message)
{
    if (mMessageQueueLock.tryLockForWrite(100))
    {
        mMessageQueue.enqueue(message);
        mMessageQueueLock.unlock();
        emit enqueuedMessage(message);
    }
    else
    {
        QString warn = QString("%1 %2 LogMessage queue lock failed: %2")
            .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs))
            .arg(LogLevel::name(message.qtMsgType())())
            .arg(message.message());
        emit warning(warn);
    }
}

void Log::unhookQtMsg()
{
    if (mOldHandler) qInstallMessageHandler(mOldHandler);
    qSetMessagePattern("%{if-category}%{category}: %{endif}"
                       "%{message}");
}

LogMessage Log::dequeueMessage()
{
    LogMessage result; // null
    if (mMessageQueueLock.tryLockForWrite(100))
    {
        if (mMessageQueue.count())
            result = mMessageQueue.dequeue();
        mMessageQueueLock.unlock();
    }
    if ( ! result.isNull())
        emit dequeuedMessage(result);
    return result;
}



// static
Log *Log::instance()
{
    static Log * spLog = nullptr;
    if (nullptr == spLog)
        spLog = new Log();
    Log * result = spLog;
    return result;
}

// global
void logMessageHandler(QtMsgType type,
              const QMessageLogContext &context,
              const QString &message)
{
    LogMessage tLM(type, context, message.toLocal8Bit());
    std::printf("%s", qPrintable(tLM.message()));
}


/*
QString qFormatLogMessage(QtMsgType type,
                          const QMessageLogContext &context,
                          const QString &str)
{
    Q_ASSERT(!"HERE!");
    Q_UNUSED(type);
    Q_UNUSED(context);
    Q_UNUSED(str);
}
*/

