#include "LogObject.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QTimer>

#include <CTextList.h>

#include "LogMachine.h"
#include "BaseLogOutput.h"
#include "LogEntry.h"
#include "LogLevel.h"

Log::Log()
    : QObject{qApp}
    , mpMachine(new LogMachine(this))
{
    setObjectName("Log");
}

Log::~Log()
{
    emit destructing();
}

void Log::start()
{
    Q_ASSERT(connect(this, &Log::destructing,
                     this, &Log::unhookQtMsg));
    emit starting();
}

void Log::hookQtMsg()
{
    static CTextList sPatternList
        = CTextList()
          << "%{function}"
          << "%{time DyyyyMMddThhmmsszzz}"
          << "%{message}"
#ifdef Q_OS_LINUX
          << "%{backtrace}"
#endif
        ;
    const CText cCTx = sPatternList.join('~');
    const QString cPattern(cCTx);
    qSetMessagePattern(cPattern);
    mOldHandler = qInstallMessageHandler(logMessageHandler);
}

void Log::add(const LogUrl &u)
{
    if (mOutputListLock.tryLockForWrite(100))
    {
//        BaseLogOutput * pOut = new BaseLogOutput(u);
  //      mOutputList.append(pOut);
        mOutputListLock.unlock();
    //    emit addedOutput(pOut);
    }
    else
    {
        QString warn = QString("%1 LogMessage output lock failed: %2")
                           .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs))
                           .arg(u.toString());
        emit warning(warn);
        std::fprintf(stderr, "%s", qPrintable(warn));
    }
}

void Log::remove(OutputPtr out)
{
    if (mOutputListLock.tryLockForWrite(100))
    {
        const Index ix = mOutputList.indexOf(out);
        if (ix > 0)
        {
            mOutputList.remove(ix);
            emit removedOutput(out);
        }
        mOutputListLock.unlock();
    }
    else
    {
        QString warn = QString("%1 LogMessage output lock failed removing: %2")
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
            .arg(LogLevel::name(message.qMsgType())())
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

void Log::enqueueEntry(const LogEntry &le)
{
    if (mMessageQueueLock.tryLockForWrite(100))
    {
        mEntryQueue.enqueue(le);
        emit enqueueEntry(le);
        emit entryQueue(mEntryQueue.count());
    }
    else
    {
        emit queuedEntryLost(le);
        QString warn = QString("%1 %2 LogEntry queue lock failed: %2")
        .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs))
            .arg(LogLevel::name(le.qMsgType())())
                           .arg(le.format()());
        emit warning(warn);
    }
}

Log::OutputList Log::outputList()
{
    Log::OutputList result;
    if (mOutputListLock.tryLockForRead(100))
    {
        result = mOutputList;
        mOutputListLock.unlock();
    }
    else
    {
        QString warn = QString("%1 LogMessage output list lock failed")
            .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs));
        emit warning(warn);
        std::fprintf(stderr, "%s", qPrintable(warn));
    }
    return result;
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
    {
        spLog = new Log();
        spLog->hookQtMsg();
        spLog->machine()->setup();
        spLog->start();
    }
    Log * result = spLog;
    return result;
}

// global
void logMessageHandler(QtMsgType type,
              const QMessageLogContext &context,
              const QString &message)
{
    LogMessage tLM(type, context, message.toLocal8Bit());
    LOG()->enqueueMessage(tLM);
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

