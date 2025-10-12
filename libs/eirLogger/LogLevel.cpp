#include "LogLevel.h"

#include <QString>

LogLevel::Value LogLevel::smFatalLevel=LogLevel::Memory;

LogLevel::LogLevel() : mValue($nullLevel), mFlag($nullLevelFlag) {;}
LogLevel::LogLevel(const Value v) : mValue(v), mFlag(Flag(1 << v)) {;}

char LogLevel::chr() const
{
    return isValidLevel() ? "0-=%#@"[msgType()] : '?';
}

bool LogLevel::isValidLevel() const
{
    return isValidLevel((int)mValue)
           && (mFlag == Flag(1 << mValue));
}

bool LogLevel::isValidLevel(const int i)
{
    return i > $nullLevel && i < $maxLevel;
}

void LogLevel::set(const int i)
{
    if (isValidLevel(i)) set((Value)i);
}

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
    case FnArg:     result = "FnArg";       break;
    case FnReturn:  result = "FnReturn";    break;
    case FnExit:    result = "FnExit";      break;
    case FnEnter:   result = "FnEnter";     break;
    case Connect:   result = "Connect";     break;
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

CText LogLevel::name(const QtMsgType qmt)
{
    CText result("?????");
    switch (qmt)
    {
    case QtInfoMsg:     result = "Info ";       break;
    case QtDebugMsg:    result = "Debug";       break;
    case QtWarningMsg:  result = "Warn ";       break;
    case QtCriticalMsg: result = "Error";       break;
    case QtFatalMsg:    result = "Fatal";       break;
    };
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

LogLevel::FlagMask LogLevel::mask(const CText &ctx)
{
    FlagMask result = $nullMask;
    if (ctx == "UserMask")          result = UserMask;
    else if (ctx == "FunctionMask") result = FunctionMask;
    else if (ctx == "TraceMask")    result = TraceMask;
    else if (ctx == "ErrorMask")    result = ErrorMask;
    return result;
}

LogLevel::MsgType LogLevel::msgType(const LogLevel::Value lvl)
{
    MsgType result = $nullMsgType;
    switch (lvl)
    {
    case UDetail:   case UInfo:
    case TDetail:   case TInfo:
    case UTrivia:   case TTrivia:       result = InfoType;      break;
    case FnExit:    case FnEnter:
    case FnReturn:
    case FnArg:
    case Dump:      case Trace:
    case DumpVal:   case DumpHex:       result = TraceType;     break;
    case $minWarning:
    case TPrefer:   case UPrefer:
    case UWarning:  case TWarning:      result = WarnType;      break;
    case $minError:
    case Error:     case Expect:        result = ErrorType;     break;
    case Memory:    case Assert:
    case Shutdown:                      result = AbortType;     break;
    case $nullLevel:
    case Minimum:   case $maxLevel:
    default:                            result = $fallbackType; break;
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
    else                        result = $fallbackType;
    return result;
}



