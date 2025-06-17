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

Log::TrollFields Log::parseTrollFields(const QString &trollMessage,
                                       const QMessageLogContext &context)
{
    TrollFields result;
    ATextList tMessageFields, tKeyList, tValueList;
    tMessageFields = trollMessage.split('\n');
    QPair<ATextList, ATextList> tPair = tMessageFields.split('=');
    for (Index ix = 0; ix < tPair.first.count(); ++ix)
    {
        AText tKey = tPair.first.at(ix);
        AText tValue = tPair.second.at(ix);
        if ("Appname" == tKey)      result.sAppname = tValue;
    }

    result.sFunction = context.function;
    return result;
}

void capturedTrollHandler(QtMsgType type,
                          const QMessageLogContext &context,
                          const QString &message)
{
    Q_UNUSED(type);
}
