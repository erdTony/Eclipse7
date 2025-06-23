#pragma once
#include "eirlogger.h"

#include <QSharedData>
#include <DataProperty.h>

#include <QtLogging>
#include <QMessageLogContext>
#include <QString>

#include <AText.h>
#include <CText.h>
#include <Types.h>

#include "LogObject.h"

typedef Log::MsgType LogMsgType;

#define QTLOGFIELDS_DATAPROPS(TND) \
    TND(CText, Appname, CText()) \
    TND(AText, Category, AText()) \
    TND(CText, FilePath, CText()) \
    TND(Count, FileLine, 0) \
    TND(AText, Message, AText()) \
    TND(unsigned, ProcessId, 0) \
    TND(unsigned, ThreadId, 0) \
    TND(qptrdiff, ThreadAddress, 0) \
    TND(LogMsgType, MsgType, Log::$nullMsgType) \
    TND(Milliseconds, BootMsec, Milliseconds()) \
    TND(AText, TimeString, CText()) \
    TND(AText, BackTrace, AText()) \
    TND(CText, FunctionName, CText()) \

class QtLogFieldsData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(QTLOGFIELDS_DATAPROPS)
public:
    QtLogFieldsData(void)
    {
        DEFINE_DATAPROPS_CTORS(QTLOGFIELDS_DATAPROPS)
    }
};

class EIRLOGGER_EXPORT QtLogFields
{
    DECLARE_PARENT_DATAPROPS(QTLOGFIELDS_DATAPROPS)
    DECLARE_DATAPROPS(QtLogFields, QtLogFieldsData)

public: // our ctors
    QtLogFields(const QString &trollMessage,
                const QMessageLogContext &context);

private: // non-const
    void set(const QString &trollMessage,
             const QMessageLogContext &context);
    void set(const AText &key, const AText &val);
};

