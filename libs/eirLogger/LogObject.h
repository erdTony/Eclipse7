#pragma once
#include "eirLogger.h"

#include <QObject>
#include <QtLogging>
#include <QQueue>
#include <QReadWriteLock>


#include <Types.h>

#include "LogEntry.h"
class AbstractLogOutput;



class EIRLOGGER_EXPORT Log : public QObject
{
    Q_OBJECT
public: // ctors
    explicit Log();

public slots:
    void start();
    void hookQtMsg();
    void unhookQtMsg();
    void add(AbstractLogOutput * out);
    void enqueue(const LogEntry &entry);

signals:
    void enqueued(const LogEntry &entry);
    void warning(const QString &message);

public: // const

public: // non-const

public: // static

public: // pointers
    static Log * instance();

private:
    QtMessageHandler mOldHandler=nullptr;
    QReadWriteLock mEntryQueueLock;
    QQueue<LogEntry> mEntryQueue;
    QList<AbstractLogOutput *> mOutputList;
};

extern EIRLOGGER_EXPORT void logMessageHandler(QtMsgType type,
                 const QMessageLogContext &context,
                 const QString &message);
