#include "LogObject.h"


ATextList Log::smPatternList = ATextList()
                               << "Appname=%{appname}"
                               << "Category=%{category}"
                               << "sFilePath=%{sFilePath}"
                               << "sFileLine=%{sFileLine}"
                               << "sMessage=%{sMessage}"
                               << "sPid=%{sPid}"
                               << "sTid=%{sTid}"
                               << "sThreadAddress=%{sThreadAddress}"
                               << "sMsgType=%{sMsgType}"
                               << "sBootMsec=%{sBootMsec}"
                               << "sTimeString=%{sTimeString}"
                               << "sBackTrace=%{sBackTrace}"
    ;

Log::Log(QObject *parent) : QObject{parent}
{
    setObjectName("Log");
}

void Log::start()
{

}

void Log::captureTroll()
{
    qSetMessagePattern(smPatternList.join('\n'));
    mOldHandler = qInstallMessageHandler(capturedTrollHandler);
}

void Log::releaseTroll()
{
    if (mOldHandler) qInstallMessageHandler(mOldHandler);
    qSetMessagePattern("%{if-category}%{category}: %{endif}%{message}");
}

QtMsgType Log::qMsgType(const MsgType mt)
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

Log::MsgType Log::msgType(const Level lvl)
{
    Log::MsgType result = $nullMsgType;
    switch (lvl)
    {
    case Detail:    case Info:      result = InfoType;  break;
    case TDetail:   case TInfo:
    case FnArg:     case FnExit:    case FnEnter:
    case TDump:     case Trace:     case TPrefer:
    case TWarning:  case TError:    result = TraceType; break;
    case Warning:                   result = WarnType;  break;
    case Error:
    case Expect:    case Assert:    result = ErrorType; break;
    case Abort:     case Memory:
    case Shutdown:  case Network:   result = AbortType; break;
    default:                        result = $fallback; break;
    }
    return result;
}

Log::MsgType Log::msgType(const AText &at)
{
    Log::MsgType result = Log::$nullMsgType;
         if ("Info"  == at)     result = InfoType;
    else if ("Trace" == at)     result = TraceType;
    else if ("Warn"  == at)     result = WarnType;
    else if ("Error" == at)     result = ErrorType;
    else if ("Abort" == at)     result = AbortType;
    else                        result = $fallback;
    return result;
}

void capturedTrollHandler(QtMsgType type,
                          const QMessageLogContext &context,
                          const QString &message)
{
    Q_UNUSED(type);
}
