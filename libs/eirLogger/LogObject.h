#pragma once
#include "eirLogger.h"

#include <QObject>
#include <QtLogging>
#include <QQueue>
#include <QReadWriteLock>


#include <Types.h>

#include "LogLevel.h"
#include "LogMessage.h"
#include "LogItem.h"
class LogOutput;
class LogEntry;
class LogMachine;


#define LOG() (Log::instance())

class EIRLOGGER_EXPORT Log : public QObject
{
    Q_OBJECT
public: // types
    typedef LogOutput * OutputPtr;
    typedef QList<OutputPtr> OutputList;

public: // ctors
    explicit Log();
    ~Log();

public slots:
    void start();
    void hookQtMsg();
    void add(OutputPtr out);
    void remove(OutputPtr out);
    void enqueueMessage(const LogMessage &message);
    void unhookQtMsg();

signals:
    void starting();
    void addedOutput(OutputPtr out);
    void removedOutput(OutputPtr out);
    void enqueuedMessage(const LogMessage &message);
    void dequeuedMessage(const LogMessage &message);
    void warning(const QString &message);
    void destructing();

public: // const

public: // non-const
    OutputList outputList();
    LogMessage dequeueMessage();

public: // static

public: // pointers
    static Log * instance();
    LogMachine * machine();

private:
    QtMessageHandler mOldHandler=nullptr;
    LogMachine * mpMachine;
    QReadWriteLock mMessageQueueLock;
    LogLevel::Flags mMessageMask;
    QQueue<LogMessage> mMessageQueue;
    QReadWriteLock mOutputListLock;
    OutputList mOutputList;
};

inline LogMachine *Log::machine() { Q_CHECK_PTR(mpMachine); return mpMachine; }

extern EIRLOGGER_EXPORT void logMessageHandler(QtMsgType type,
                 const QMessageLogContext &context,
                 const QString &message);
