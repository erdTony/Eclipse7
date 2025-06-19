#pragma once

#include <AText.h>
#include <FileInfo.h>
#include <FunctionInfo.h>
#include <Types.h>

#include "LogObject.h"

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

private:
    Log::Level      mLevel;
    FileInfo        mFilePath;
    Count           mFileLine;
    AText           mQFuncInfo;
    FunctionInfo    mFunctionInfo;
};

inline Log::Level LogContext::level() const { return mLevel; }
inline Log::MsgType LogContext::msgType() const { return Log::msgType(level()); }


