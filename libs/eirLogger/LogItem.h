#pragma once
#include "eirlogger.h"


#include <QSharedData>

#include <DataProperty.h>

#include <QUuid>
#include <QVariant>
#include <QVariantList>

#include <AText.h>
#include <Types.h>
#include <UText.h>

#include "LogContext.h"
#include "LogObject.h"

typedef Log::Level LogLevel;
typedef Log::Operation LogOperation;

#define LOGITEM_DATAPROPS(TND) \
    TND(Milliseconds,   timeStamp,      0) \
    TND(QUuid,          itemUid,        QUuid()) \
    TND(LogContext,     context,        LogContext()) \
    TND(AText,          message,        AText()) /*TODO UText*/ \
    TND(UText,          format,         UText()) \
    TND(AText,          printF,         AText()) \
    TND(QVariantList,   values,         QVariantList()) \
    TND(LogOperation,   operation,      LogOperation()) \
    TND(AText,          expectedName,   AText()) \
    TND(QVariant,       expectedValue,  QVariant()) \
    TND(AText,          actualName,     AText()) \
    TND(QVariant,       actualValue,    QVariant()) \

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
