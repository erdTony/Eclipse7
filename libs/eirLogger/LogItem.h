#pragma once
#include "eirLogger.h"


#include <QSharedData>
#include <DataProperty.h>

#include <QList>
#include <QLoggingCategory>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantList>
class QDomDocument;
class QSqlRecord;

#include <AText.h>
#include <Types.h>
#include <Uid.h>
#include <UText.h>

#include "LogCondition.h"
#include "LogLevel.h"
#include "LogFileInfo.h"
#include "LogFuncInfo.h"
class LogMessage;

#define LOGITEM_DATAPROPS(TND) \
    TND(LogLevel,           level,          LogLevel()) \
    TND(Milliseconds,       timeStamp,      0) \
    TND(Uid,                logUid,         Uid()) \
    TND(LogFileInfo,        fileInfo,       LogFileInfo()) \
    TND(uint,               fileLine,       0) \
    TND(LogFuncInfo,        funcInfo,       LogFuncInfo()) \
    TND(UText,              format,         UText()) \
    TND(LogCondition,       condition,      LogCondition()) \
    TND(QVariantList,       values,         QVariantList()) \

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
public: // types

public: // our ctors
    LogItem(const LogMessage &lm);

public: // const
    bool isNull() const;
    bool isWarn() const;
    bool isError() const;
    bool isFatal() const;
    QString displayString() const;
    QStringList formatStringList() const;
    QDomDocument formatXmlDocument() const;
    QSqlRecord formatSqlRecord() const;

public: // non-const
    void set(const LogMessage &lm);
    void setUid();

public: // pointers
    const LogItem it() const;
    const LogItem & it();

private:
    QString formattedMessage() const;
    bool isValidValueIndex(const qsizetype ix) const;
    QVariant value(const qsizetype ix) const;
    QString valueString(const qsizetype ix) const;

private:
    QList<QVariant> mFormatVariantList;
};

inline bool LogItem::isWarn() const { return level().value() > LogLevel::$minWarning; }
inline bool LogItem::isError() const { return level().value() > LogLevel::$minError; }
inline bool LogItem::isFatal() const { return level().value() > LogLevel::$minFatal; }
inline const LogItem LogItem::it() const { return *this; }
inline const LogItem &LogItem::it() { return *this; }
