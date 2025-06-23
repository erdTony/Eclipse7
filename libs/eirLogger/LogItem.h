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
    TND(Milliseconds, TimeStamp, 0) \
    TND(Uid, ItemUid, Uid()) \
    TND(LogContext, Context, LogContext()) \
    TND(AText, Message, AText()) /*TODO UText*/ \
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
    LogItem(const LogContext ctx, const char * msg);

public: // const
    bool isNull() const;
    bool isWarn() const;

public: // non-const
    void setUid();

public: // pointer
    const LogItem it() const;
};

inline const LogItem LogItem::it() const { return *this; }
