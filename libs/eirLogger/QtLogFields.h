#pragma once

#include <QSharedDataPointer>

#include <QtLogging>
#include <QMessageLogContext>
#include <QString>

#include "AText.h"
#include "FileName.h"
#include "FilePath.h"
#include "FunctionName.h"
#include "TimeString.h"
#include "Types.h"

class QtLogFieldsData : public QSharedData
{
public:
    FileName            dAppname;
    AText               dCategory;
    FilePath            dFilePath;
    Count               dFileLine;
    AText               dMessage;
    unsigned            dProcessId;
    unsigned            dThreadId;
    qptrdiff            dThreadAddress;
    QtMsgType           dMsgType;
    EpochMilliseconds   dBootMsec;
    TimeString          dTimeString;
    AText               dBackTrace;
    FunctionName        dFunction;
};

class QtLogFields
{
public: // data

public: // our ctors
    QtLogFields(const QString &trollMessage,
                const QMessageLogContext &context);

public: // const

public: // non-const
    void set(const QString &trollMessage,
             const QMessageLogContext &context);
    void set(const AText &key, const AText &val);


    // ======== For QSharedDataPointer =======
public:
    QtLogFields();
    QtLogFields(const QtLogFields &);
    QtLogFields(QtLogFields &&);
    QtLogFields &operator=(const QtLogFields &);
    QtLogFields &operator=(QtLogFields &&);
    ~QtLogFields();

private:
    QSharedDataPointer<QtLogFieldsData> data;
};
