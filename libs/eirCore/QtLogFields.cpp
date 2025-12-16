#include "QtLogFields.h"

#include <utility>

#include <AText.h>
#include <ATextList.h>

#include "QtLogFields.h"

DEFINE_DATAPROPS(QtLogFields, QtLogFieldsData)

QtLogFields::QtLogFields(const QString &trollMessage,
                         const QMessageLogContext &context)
{ set(trollMessage, context); }
void QtLogFields::ctor(void) {;}
void QtLogFields::dtor(void) {;}

void QtLogFields::set(const QString &trollMessage, const QMessageLogContext &context)
{
    const AText cTrollText(trollMessage);
    const ATextList cTrollList = cTrollText.toList('\n');
    const ATextList::Pair cTrollPair = cTrollList.split('=');
    ATextList tTrollKeys = cTrollPair.first;
    ATextList tTrollVals = cTrollPair.second;
    while ( ! tTrollKeys.isEmpty() &&  ! tTrollVals.isEmpty())
        set(tTrollKeys.takeFirst(), tTrollVals.takeFirst());
    set("Function", context.function);
}

void QtLogFields::set(const AText &key, const AText &val)
{
#if 0
    if ("Appname" == key)           setAppname(val);
    if ("Category" == key)          setCategory(val);
    if ("FilePath" == key)          setFilePath(val);
    if ("FileLine" == key)          setFileLine(val.toInt());
    if ("Message" == key)           setMessage(val);
    if ("ProcessId" == key)         setProcessId(val.toInt());
    if ("ThreadId" == key)          setThreadId(val.toInt());
    if ("ThreadAddress" == key)     setThreadAddress(val.toInt());
    if ("MsgType" == key)           setMsgType(Log::msgType(val));
    if ("BootMsec" == key)          setBootMsec(val.toInt());
    if ("TimeString" == key)        setTimeString(val);
    if ("BackTrace" == key)         setBackTrace(val);
    if ("FunctionName" == key)      setFunctionName(val);
#endif
}

