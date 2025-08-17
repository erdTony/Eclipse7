#pragma once
#include "eirLogger.h"

#include <QObject>
#include <QtLogging>
#include <QQueue>
#include <QReadWriteLock>


#include <Types.h>

#include "LogEntry.h"
#include "LogItem.h"
class AbstractLogOutput;



class EIRLOGGER_EXPORT Log : public QObject
{
    Q_OBJECT
public: // ctors
    explicit Log();
    ~Log();

public slots:
    void start();
    void hookQtMsg();
    void add(AbstractLogOutput * out);
    void enqueueEntry(const LogEntry &entry);
    void enqueueItem();
    void pulse();
    void unhookQtMsg();

signals:
    void starting();
    void added(AbstractLogOutput * out);
    void enqueuedEntry(const LogEntry &entry);
    void dequeuedEntry(const LogEntry &entry);
    void enqueuedItem(const LogItem &item);
    void warning(const QString &message);
    void destructing();

public: // const

public: // non-const
    LogEntry dequeueEntry();

public: // static

public: // pointers
    static Log * instance();

private:
    QtMessageHandler mOldHandler=nullptr;
    QReadWriteLock mEntryQueueLock;
    QQueue<LogEntry> mEntryQueue;
    QReadWriteLock mItemQueueLock;
    QQueue<LogItem> mItemQueue;
    QList<AbstractLogOutput *> mOutputList;
};

extern EIRLOGGER_EXPORT void logMessageHandler(QtMsgType type,
                 const QMessageLogContext &context,
                 const QString &message);
