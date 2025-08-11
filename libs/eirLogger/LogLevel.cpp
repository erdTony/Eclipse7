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
    case UTrivia:   result = "UTrivia";     break;
    case TDetail:   result = "TDetail";     break;
    case DumpVal:   result = "DumpVal";     break;
    case Dump:      result = "Dump";        break;
    case Trace:     result = "Trace";       break;
    case TInfo:     result = "TInfo";       break;
    case TPrefer:   result = "TPrefer";     break;
    case UPrefer:   result = "UPrefer";     break;
    case TProgress: result = "TProgress";   break;
    case UProgress: result = "UProgress";   break;
    case TWarning:  result = "TWarning";    break;
    case UWarning:  result = "UWarning";    break;
    case Error:     result = "Error";       break;
    case Expect:    result = "Expect";      break;
    case Memory:    result = "Memory";      break;
    case Assert:    result = "Assert";      break;
    case Shutdown:  result = "Shutdown";    break;
    default:        /* Ignore */            break;
    }
    return result;
}


QtMsgType LogLevel::qMsgType(const MsgType mt)
{
    QtMsgType result = QtWarningMsg;
    switch (mt)
    {
    case $nullMsgType:                          break;
    case InfoType:      result = QtInfoMsg;     break;
    case TraceType:     result = QtDebugMsg;    break;
    case WarnType:      result = QtWarningMsg;  break;
    case ErrorType:     result = QtCriticalMsg; break;
    case AbortType:     result = QtFatalMsg;    break;
    }
    return result;
}

LogLevel::MsgType LogLevel::msgType(const LogLevel::Value lvl)
{
    MsgType result = $nullMsgType;
    switch (lvl)
    {
    case UDetail:   case UInfo:      result = InfoType;  break;
    case TDetail:   case TInfo:
    case FnExit:    case FnEnter:
    case Dump:      case Trace:     case TPrefer:
    case TWarning:  result = TraceType; break;
    case UWarning:                   result = WarnType;  break;
    case Error:
    case Expect:    case Assert:    result = ErrorType; break;
    case Memory:
    case Shutdown:  result = AbortType; break;
    default:                        result = $fallback; break;
    }
    return result;
}


LogLevel::MsgType LogLevel::msgType(const CText &ct)
{
    MsgType result = $nullMsgType;
         if ("Info"  == ct)     result = InfoType;
    else if ("Trace" == ct)     result = TraceType;
    else if ("Warn"  == ct)     result = WarnType;
    else if ("Error" == ct)     result = ErrorType;
    else if ("Abort" == ct)     result = AbortType;
    else                        result = $fallback;
    return result;
}



