#pragma once
#include "eirLogger.h"

#include <QSharedDataPointer>
#include <QHash>

#include <AText.h>

class LogFuncInfoData;

class EIRLOGGER_EXPORT LogFuncInfo
{
public: // our ctors
    LogFuncInfo(const AText &funcName);

public: // const
    QString qFuncInfo() const;

public: // data
    LogFuncInfo();
    LogFuncInfo(const LogFuncInfo &other);
    LogFuncInfo(LogFuncInfo &&rother);
    LogFuncInfo &operator=(const LogFuncInfo &rhs);
    LogFuncInfo &operator=(LogFuncInfo &&rhs);
    ~LogFuncInfo();
private:
    QSharedDataPointer<LogFuncInfoData> data;
//    static QHash<AText, LogFuncInfo> smFuncInfoHash;
};
