#include "LogObject.h"

#include <QCoreApplication>
#include <QDateTime>

#include <CTextList.h>

#include "AbstractLogOutput.h"
#include "LogLevel.h"

Log::Log() : QObject{qApp}
{
    setObjectName("Log");
}

void Log::start()
{

}

void Log::hookQtMsg()
{
    static CTextList sPatternList
        = CTextList()
          << "Appname=%{Appname}"
          << "Category=%{Category}"
          << "FilePath=%{FilePath}"
          << "FileLine=%{FileLine}"
          << "Message=%{Message}"
          << "Pid=%{Pid}"
          << "Tid=%{Tid}"
          << "ThreadAddress=%{ThreadAddress}"
          << "MsgType=%{MsgType}"
          << "BootMsec=%{BootMsec}"
          << "TimeString=%{TimeString}"
          << "BackTrace=%{BackTrace}";
    qSetMessagePattern(sPatternList.join('\n'));
    mOldHandler = qInstallMessageHandler(logMessageHandler);
}

void Log::unhookQtMsg()
{
    if (mOldHandler) qInstallMessageHandler(mOldHandler);
    qSetMessagePattern("%{if-category}%{category}: %{endif}"
                       "%{message}");
}

void Log::add(AbstractLogOutput *out)
{
    out->setParent(this);
    mOutputList.append(out);
}

void Log::enqueue(const LogEntry &entry)
{
    if (mEntryQueueLock.tryLockForWrite(100))
    {
        mEntryQueue.enqueue(entry);
        mEntryQueueLock.unlock();
        emit enqueued(entry);
    }
    else
    {
        QString warn = QString("%1 LogEntry queue lock failed: %1")
            .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs))
            .arg(entry.level().name()());
        emit warning(warn);
    }
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
    Q_UNUSED(message);
}
