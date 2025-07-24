#pragma once

#include <AText.h>
#include <Types.h>

#include <AText.h>

#include "LogFileInfo.h"
#include "LogFuncInfo.h"
#include "LogObject.h"

class LogContext
{
public:
    LogContext();
    LogContext(const Log::Level level,
               const char * qFuncInfo,
               const char * fileName,
               const Count fileLine);

public: // const
    Log::Level level() const;
    Log::MsgType msgType() const;
    AText qFuncInfo() const;
    LogFileInfo fileInfo() const;
    AText baseFileName() const;

private:
    Log::Level      mLevel;
    LogFileInfo     mLogFileInfo;
    Count           mFileLine;
    AText           mQFuncInfo;
    LogFuncInfo     mLogFuncInfo;
};

inline Log::Level LogContext::level() const { return mLevel; }
inline Log::MsgType LogContext::msgType() const { return Log::msgType(level()); }
inline AText LogContext::qFuncInfo() const { return mQFuncInfo; }
inline LogFileInfo LogContext::fileInfo() const { return mLogFileInfo; }


