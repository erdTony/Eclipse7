#pragma once

#include <AText.h>
#include <FileInfo.h>
#include <FunctionInfo.h>
#include <Types.h>

#include <AText.h>

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
    FileInfo fileInfo() const;
    AText baseFileName() const;

private:
    Log::Level      mLevel;
    FileInfo        mFileInfo;
    Count           mFileLine;
    AText           mQFuncInfo;
    FunctionInfo    mFunctionInfo;
};

inline Log::Level LogContext::level() const { return mLevel; }
inline Log::MsgType LogContext::msgType() const { return Log::msgType(level()); }
inline AText LogContext::qFuncInfo() const { return mQFuncInfo; }
inline FileInfo LogContext::fileInfo() const { return mFileInfo; }


