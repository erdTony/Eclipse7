#pragma once
#include "eirCore.h"

#include <QSharedDataPointer>
#include <QHash>

#include <AText.h>
#include <CText.h>

class LogFuncInfoData;

class EIRCORE_EXPORT LogFuncInfo
{
public: // our ctors
    LogFuncInfo(const AText &qfi);

public: // const
    CText className() const;
    CText functionName() const;
    AText qFuncInfo() const;
    bool operator == (const LogFuncInfo &rhs) const;
    bool operator != (const LogFuncInfo &rhs) const;

public: // non-const
    void set(const AText &qfi);

public: // QSharedDataPointer
    LogFuncInfo();
    LogFuncInfo(const LogFuncInfo &other);
    LogFuncInfo(LogFuncInfo &&rother);
    LogFuncInfo &operator=(const LogFuncInfo &rhs);
    LogFuncInfo &operator=(LogFuncInfo &&rhs);
    ~LogFuncInfo();
private:
    QSharedDataPointer<LogFuncInfoData> data;
};
