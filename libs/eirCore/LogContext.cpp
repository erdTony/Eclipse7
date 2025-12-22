#include "LogContext.h"


LogContext::LogContext(const char * const qfi, const char * const file, const int line)
    : mQFI(qfi), mFileName(file), mLine(line) {;}

FileInfo LogContext::fileInfo() const
{

}

FunctionInfo LogContext::functionInfo() const
{
    static FunctionInfo result;
    if (result.isNull()) result.set(qfi());
    return result;
}

