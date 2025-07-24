#pragma once

#include <QObject>

#include <QMap>
#include <QQueue>

class QTimer;

#include <Types.h>
#include <Url.h>

#include "LogItem.h"
#include "LogObject.h"

class BaseLogOutput;

class Logger : public QObject
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
    bool addOutput(const Url &url);

public: // pointers

private slots:
    void initialize();
    void handleInputQueue();
    void poll();

private:
    bool addTrollOutput();
    bool addStdioOutput();
    bool addTextFileOutput(const LogFileInfo &fi);


private:
    QTimer * mpInputTimer=nullptr;
    QTimer * mpPollTimer=nullptr;
    ItemQueue mInputQueue;
    QMap<Log::MsgType, ItemQueue> mTypeQueueMap;
    QMap<Url, BaseLogOutput *> mUrlOutputMap;


    // ======= Properties ========
    Milliseconds mHiPollMsec;
    Milliseconds mLoPollMsec;
};
