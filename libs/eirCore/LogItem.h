#pragma once
#include "eirCore.h"


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
#include "LogFile.h"
#include "LogFuncInfo.h"
class LogMessage;

#define LOGITEM_DATAPROPS(TND) \
    TND(LogLevel,           level,          LogLevel()) \
    TND(MilliSeconds,       timeStamp,      0) \
    TND(Uid,                logUid,         Uid()) \
    TND(LogFile,            file,           LogFile()) \
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

class EIRCORE_EXPORT LogItem
{
    DECLARE_PARENT_DATAPROPS(LOGITEM_DATAPROPS);
    DECLARE_DATAPROPS(LogItem, LogItemData);
public: // types

public: // our ctors
    LogItem(const LogMessage &lm);

public: // const
    bool isNull() const;
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
};

inline const LogItem LogItem::it() const { return *this; }
inline const LogItem &LogItem::it() { return *this; }
