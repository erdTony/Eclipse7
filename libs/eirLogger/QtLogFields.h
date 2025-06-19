#pragma once
#include "eirlogger.h"

#include <QSharedData>
#include <DataProperty.h>

#include <QtLogging>
#include <QMessageLogContext>
#include <QString>

#include "AText.h"
#include "FileName.h"
#include "FilePath.h"
#include "FunctionName.h"
#include "TimeString.h"
#include "Types.h"

#define QTLOGFIELDS_DATAPROPS(TND) \
    TND(FileName, Appname, FileName()) \
    TND(AText, Category, AText()) \
    TND(FilePath, FilePath, FilePath()) \
    TND(Count, FileLine, 0) \
    TND(AText, Message, AText()) \
    TND(unsigned, ProcessId, 0) \
    TND(unsigned, ThreadId, 0) \
    TND(qptrdiff, ThreadAddress, 0) \
    TND(QtMsgType, MsgType, QtInfoMsg) \
    TND(EpochMilliseconds, BootMsec, EpochMilliseconds()) \
    TND(TimeString, TimeString, TimeString()) \
    TND(AText, BackTrace, AText()) \
    TND(FunctionName, FunctionName, FunctionName()) \

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

