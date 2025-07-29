#pragma once

#include <Enumeration.h>

#define LOGLEVEL_NAMEVAL(NVAL) \
    NVAL($nullLevel, 0) \
    NVAL(Minimum, 1) \
    NVAL(FnArgVal, 3) \
    NVAL(FnArgName, 4) \
    NVAL(FnReturn, 6) \
    NVAL(FnExit, 7) \
    NVAL(FnEnter, 9) \
    NVAL(TTrivia, 11) \
    NVAL(ITrivia, 12) \
    NVAL(TDetail, 14) \
    NVAL(IDetail, 15) \
    NVAL(DumpVal, 16) \
    NVAL(Dump, 17) \
    NVAL(Trace, 20) \
    NVAL(TInfo, 22) \
    NVAL(Info, 23) \
    NVAL(TProgress, 25) \
    NVAL(IProgress, 26) \
    NVAL(TPrefer, 41) \
    NVAL(IPrefer, 42) \
    NVAL(Expect, 51) \
    NVAL(Memory, 57) \
    NVAL(Assert, 59) \
    NVAL(Shutdown, 61) \
    NVAL(Maximum, 63) \


DEFINE_ENUMT_NAMEVAL(LogLevelEnum, BYTE, LOGLEVEL_NAMEVAL);

DEFINE_FLAG_NAME(LogLevelFlag, quint64, LOGLEVEL_NAMEVAL);


/*
class LogLevel
{
public:
    LogLevel();
};
*/

