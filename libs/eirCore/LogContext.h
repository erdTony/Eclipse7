#pragma once

#include "CText.h"
#include "FileInfo.h"
#include "FunctionInfo.h"
#include "FSText.h"

#define LOGCONTEXT LogContext(Q_FILE_INFO, __FILE__, __LINE__)

class LogContext
{
public:
    LogContext(const char * const qfi, const char * const file, const int line);
    CText qfi() const;
    FSText fileName() const;
    int line() const;
    FileInfo fileInfo() const;
    FunctionInfo functionInfo() const;

private:
    CText mQFI;
    FSText mFileName;
    int mLine=-1;
};

inline CText LogContext::qfi() const
{

}

inline FSText LogContext::fileName() const
{

}

inline int LogContext::line() const
{

}
