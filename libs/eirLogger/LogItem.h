#pragma once

#include <QSharedDataPointer>

#include <QVariant>
#include <QVariantList>

#include <Uid.h>
#include <Types.h>

#include "LogContext.h"
#include "LogObject.h"

class LogItemData;

class LogItem
{
public: // data
    Uid                 dItemUid;
    Log::Level          dLevel;
    LogContext          dContext;
    EpochMilliseconds   dEms;
    UText               dMessage;
    UText               dFormat;
    AText               dPrintF;
    QVariantList        dValues;
    Log::Operation      dOperation;
    AText               dExpectedName;
    QVariant            dExpectedValue;
    AText               dActualName;
    QVariant            dActualValue;

public: // our ctors


public: // const
    bool isNull() const;

public: // non-const



public: // static non-const
    static bool isEmpty();
    static Count queueCount();
    static void enqueue();
    static bool eequeue(LogItem * pItem);

private: // static
    static QQueue<LogItem> smItemQueue;

    // ========= built in QSharedDataPointer ========
public:
    LogItem();
    LogItem(const LogItem &);
    LogItem(LogItem &&);
    LogItem &operator=(const LogItem &);
    LogItem &operator=(LogItem &&);
    ~LogItem();
private:
    QSharedDataPointer<LogItemData> data;
};
