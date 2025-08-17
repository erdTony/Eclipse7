#pragma once
#include "eirLogger.h"

#include <QSharedDataPointer>
#include <QHash>

#include <AText.h>

class LogFuncInfoData;

class EIRLOGGER_EXPORT LogFuncInfo
{
public:
    LogFuncInfo();
    LogFuncInfo(const LogFuncInfo &);
    LogFuncInfo(LogFuncInfo &&);
    LogFuncInfo &operator=(const LogFuncInfo &);
    LogFuncInfo &operator=(LogFuncInfo &&);
    ~LogFuncInfo();

private:
    QSharedDataPointer<LogFuncInfoData> data;
    static QHash<AText, LogFuncInfo> smFuncInfoHash;
};
