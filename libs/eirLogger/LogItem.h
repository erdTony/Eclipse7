#pragma once
#include "eirLogger.h"


#include <QSharedData>

#include <DataProperty.h>

#include <QLoggingCategory>
#include <QUuid>
#include <QVariant>
#include <QVariantList>

#include <AText.h>
#include <Types.h>
#include <UText.h>

#include "LogEntry.h"
#include "LogLevel.h"
#include "LogFileInfo.h"
#include "LogFuncInfo.h"

#define LOGITEM_DATAPROPS(TND) \
    TND(LogLevel,           level,          LogLevel()) \
    TND(Milliseconds,       timeStamp,      0) \
    TND(Uid,                logUid,         Uid()) \
    TND(LogEntry,           logEntry,       LogEntry()) \
    TND(LogFileInfo,        fileInfo,       LogFileInfo()) \
    TND(uint,               fileLine,       0) \
    TND(LogFuncInfo,        funcInfo,       LogFuncInfo()) \
    TND(UText,              format,         UText()) \
    TND(AText,              printF,         AText()) \
    TND(LogCondition,       cond,           LogCondition()) \
    TND(QVariantList,       values,         QVariantList()) \
    TND(AText,              expectedName,   AText()) \
    TND(QVariant,           expectedValue,  QVariant()) \
    TND(AText,              actualName,     AText()) \
    TND(QVariant,           actualValue,    QVariant()) \

class LogItemData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(LOGITEM_DATAPROPS);
public:
    LogItemData(void)
    {
        DEFINE_DATAPROPS_CTORS(LOGITEM_DATAPROPS);
    }
};

class EIRLOGGER_EXPORT LogItem
{
    DECLARE_PARENT_DATAPROPS(LOGITEM_DATAPROPS);
    DECLARE_DATAPROPS(LogItem, LogItemData);
public: // data

public: // our ctors
//    LogItem(const char * msg);
    LogItem(const LogEntry &le);

public: // const
    bool isNull() const;
    bool isWarn() const;
    QString formattedMessage() const;

public: // non-const
    void set(const LogEntry &le);
    void setUid();

public: // pointer
    const LogItem it() const;
};

inline const LogItem LogItem::it() const { return *this; }
