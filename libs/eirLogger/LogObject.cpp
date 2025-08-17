#include "LogObject.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QTimer>

#include <CTextList.h>

#include "AbstractLogOutput.h"
#include "LogLevel.h"
#include "LogObject.h"

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
          << "Appname=%{appname}"
          << "Category=%{category}"
          << "FilePath=%{file}"
          << "FileLine=%{line}"
          << "Message=%{message}"
          << "Pid=%{pid}"
          << "Tid=%{threadid}"
          << "ThreadAddress=%{qthreadptr}"
          << "MsgType=%{type}"
          << "BootMsec=%{time boot}"
#ifndef Q_OS_WINDOWS
          << "BackTrace=%{backtrace}"
#endif
          << "TimeString=%{time DyyyyMMddThhmmsszzz}";
    const CText cCTx = sPatternList.join('~');
    const QString cPattern(cCTx);
    qSetMessagePattern(cPattern);
    mOldHandler = qInstallMessageHandler(logMessageHandler);
}

void Log::unhookQtMsg()
{
    if (mOldHandler) qInstallMessageHandler(mOldHandler);
    qSetMessagePattern("%{if-category}%{category}: %{endif}"
                       "%{message}");
}

LogEntry Log::dequeueEntry()
{
    LogEntry result; // null
    if (mEntryQueueLock.tryLockForWrite(100))
    {
        if (mEntryQueue.count())
            result = mEntryQueue.dequeue();
        mEntryQueueLock.unlock();
    }
    if ( ! result.isNull())
    emit dequeuedEntry(result);
    return result;
}

void Log::add(AbstractLogOutput *out)
{
    out->setParent(this);
    mOutputList.append(out);
}


void Log::enqueueEntry(const LogEntry &entry)
{
    if (mEntryQueueLock.tryLockForWrite(100))
    {
        mEntryQueue.enqueue(entry);
        mEntryQueueLock.unlock();
        emit enqueuedEntry(entry);
    }
    else
    {
        QString warn = QString("%1 LogEntry queue lock failed: %1")
            .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs))
            .arg(entry.level().name()());
        emit warning(warn);
    }
}

void Log::enqueueItem()
{
    LogEntry tLE = dequeueEntry();
    if ( ! tLE.isNull())
    {
        LogItem tItem(tLE);
        if (mItemQueueLock.tryLockForWrite(100))
        {
            mItemQueue.enqueue(tItem);
            mItemQueueLock.unlock();
            emit enqueuedItem(tItem);
        }
        else
        {
            enqueueEntry(tLE);
        }
    }
    else
    {
        if (mEntryQueue.count())
            QTimer::singleShot(150, this, &Log::pulse);
    }
}

void Log::pulse()
{
    // TODO Log::pulse()
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
    Q_UNUSED(type);
    Q_UNUSED(context);
    LogEntry tLE(message.toLocal8Bit());
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

