#include "LogLevel.h"

#include <QString>

LogLevel::LogLevel() : mValue($nullLevel), mFlag($nullLevelFlag) {;}
LogLevel::LogLevel(const Value v) : mValue(v), mFlag(Flag(1 << v)) {;}

void LogLevel::set(const Value v)
{
    mValue = v, mFlag = Flag(1 << v);
}



// static
CText LogLevel::name(const Value v)
{
    CText result = QString("Unknown %1").arg(v, 10, 2, '0');
    switch (v)
    {
    case FnArgVal:  result = "FnArgVal";    break;
    case FnArgName: result = "FnArgName";   break;
    case FnReturn:  result = "FnReturn";    break;
    case FnExit:    result = "FnExit";      break;
    case FnEnter:   result = "FnEnter";     break;
    case TTrivia:   result = "TTrivia";     break;
    case ITrivia:   result = "ITrivia";     break;
    case TDetail:   result = "TDetail";     break;
    case DumpVal:   result = "DumpVal";     break;
    case Dump:      result = "Dump";        break;
    case Trace:     result = "Trace";       break;
    case TInfo:     result = "TInfo";       break;
    case TPrefer:   result = "TPrefer";     break;
    case IPrefer:   result = "IPrefer";     break;
    case TProgress: result = "TProgress";   break;
    case IProgress: result = "IProgress";   break;
    case TWarning:  result = "TWarning";    break;
    case IWarning:  result = "IWarning";    break;
    case Error:     result = "Error";       break;
    case Expect:    result = "Expect";      break;
    case Memory:    result = "Memory";      break;
    case Assert:    result = "Assert";      break;
    case Shutdown:  result = "Shutdown";    break;
    default:        /* Ignore */            break;
    }
    return result;
}



