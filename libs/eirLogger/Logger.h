#pragma once
#include "eirLogger.h"

#include <QObject>

#include <QMap>
#include <QQueue>
#include <QUrl>
class QTimer;

#include <Types.h>

#include "LogFile.h"
#include "LogItem.h"
#include "LogLevel.h"
#include "LogObject.h"

class AbstractLogOutput;

class EIRLOGGER_EXPORT Logger : public QObject
{
    Q_OBJECT
public: // types
    typedef QQueue<LogItem> ItemQueue;

public: // ctors
    explicit Logger(QObject *parent = nullptr);

public slots:
    void enqueue(const LogItem & item);

signals:
    void initialized();
    void inputQueued(const LogItem & Item);

public: // const
    bool inputEmpty();
    Count inputCount();

public: // non-const
    bool addOutput(const QUrl &url);

public: // pointers

private slots:
    void initialize();
    void handleInputQueue();
    void poll();

private:
    bool addTrollOutput();
    bool addStdioOutput();
    bool addTextFileOutput(const LogFile &lf);


private:
    QTimer * mpInputTimer=nullptr;
    QTimer * mpPollTimer=nullptr;
    ItemQueue mInputQueue;
    QMap<LogLevel::MsgType, ItemQueue> mTypeQueueMap;
    QMap<QUrl, AbstractLogOutput *> mUrlOutputMap;


    // ======= Properties ========
    Milliseconds mHiPollMsec;
    Milliseconds mLoPollMsec;
};
