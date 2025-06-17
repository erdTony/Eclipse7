#pragma once

#include <AText.h>
#include <FileInfo.h>
#include <FunctionInfo.h>
#include <Types.h>

class LogContext
{
public:
    LogContext();
    LogContext(const char * qFuncInfo,
               const char * fileName,
               const Count fileLine);

private:
    FileInfo        mFilePath;
    Count           mFileLine;
    AText           mQFuncInfo;
    FunctionInfo    mFunctionInfo;
};
