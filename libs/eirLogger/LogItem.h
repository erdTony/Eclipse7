#pragma once
#include "eirlogger.h"


#include <QSharedData>

#include <DataProperty.h>

#include <QVariant>
#include <QVariantList>

#include <AText.h>
#include <MillisecondTime.h>
#include <Types.h>
#include <Uid.h>
#include <UText.h>

#include "LogContext.h"
#include "LogObject.h"

typedef Log::Level LogLevel;
typedef Log::Operation LogOperation;

#define LOGITEM_DATAPROPS(TND) \
    TND(EpochMilliseconds, TimeStamp, 0) \
    TND(LogLevel, Level, LogLevel::$nullLevel) \
    TND(Uid, ItemUid, Uid()) \
    TND(LogContext, Context, LogContext()) \
    TND(UText, Format, UText()) \
    TND(AText, PrintF, AText()) \
    TND(QVariantList, Values, QVariantList()) \
    TND(LogOperation, Operation, LogOperation()) \
    TND(AText, ExpectedName, AText()) \
    TND(QVariant, ExpectedValue, QVariant()) \
    TND(AText, ActualName, AText()) \
    TND(QVariant, ActualValue, QVariant()) \

class LogItemData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(LOGITEM_DATAPROPS)
public:
    LogItemData(void)
    {
        DEFINE_DATAPROPS_CTORS(LOGITEM_DATAPROPS)
    }
};

class EIRLOGGER_EXPORT LogItem
{
    DECLARE_PARENT_DATAPROPS(LOGITEM_DATAPROPS)
    DECLARE_DATAPROPS(LogItem, LogItemData)
public: // data

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

};
