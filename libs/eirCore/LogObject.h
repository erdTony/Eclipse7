#pragma once
#include "eirCore.h"

#include <QObject>
#include <QtLogging>
#include <QQueue>
#include <QReadWriteLock>


#include <Types.h>

#include "LogLevel.h"
#include "LogMessage.h"
#include "LogItem.h"
class BaseLogOutput;
class LogEntry;
class LogMachine;
class LogUrl;

#ifndef LOG
#define LOG() (Log::instance())
#endif

class EIRCORE_EXPORT Log : public QObject
{
    Q_OBJECT
public: // types
    typedef BaseLogOutput * OutputPtr;
    typedef QList<OutputPtr> OutputList;

public: // ctors
    explicit Log();
    ~Log();

public slots:
    void start();
    void hookQtMsg();
    void add(const LogUrl &u);
    void remove(OutputPtr out);
    void enqueueMessage(const LogMessage &message);
    void unhookQtMsg();

signals:
    void starting();
    void addedOutput(OutputPtr out);
    void removedOutput(OutputPtr out);
    void enqueuedEntry(const LogEntry &le);
    void queuedEntryLost(const LogEntry &le);
    void dequeuedEntry(const LogEntry &le);
    void entryQueue(const Count count);
    void enqueuedMessage(const LogMessage &message);
    void dequeuedMessage(const LogMessage &message);
    void warning(const QString &message);
    void destructing();

public: // const

public: // non-const
    void enqueueEntry(const LogEntry &le);
    OutputList outputList();
    LogMessage dequeueMessage();

public: // static

public: // pointers
    static Log * instance();
    LogMachine * machine();

private:
    QtMessageHandler mOldHandler=nullptr;
    LogMachine * mpMachine=nullptr;
    QReadWriteLock mEntryQueueLock;
    QQueue<LogEntry> mEntryQueue;
    QReadWriteLock mMessageQueueLock;
    LogLevel::Flags mMessageMask;
    QQueue<LogMessage> mMessageQueue;
    QReadWriteLock mOutputListLock;
    OutputList mOutputList;
};

inline LogMachine *Log::machine() { Q_CHECK_PTR(mpMachine); return mpMachine; }

extern EIRCORE_EXPORT void logMessageHandler(QtMsgType type,
                 const QMessageLogContext &context,
                 const QString &message);
