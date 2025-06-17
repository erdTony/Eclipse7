#include "QtLogFields.h"

#include <utility>

#include <AText.h>
#include <ATextList.h>


QtLogFields::QtLogFields(const QString &trollMessage, const QMessageLogContext &context) { set(trollMessage, context); }

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
    if ("Appname" == key)           data->dAppname = val;
    if ("Category" == key)          data->dCategory = val;
    if ("FilePath" == key)          data->dFilePath = val;
    if ("FileLine" == key)          data->dFileLine = val.toInt();
    if ("Message" == key)           data->dMessage = val;
    if ("ProcessId" == key)         data->dProcessId = val.toInt();
    if ("ThreadId" == key)          data->dThreadId = val.toInt();
    if ("ThreadAddress" == key)     data->dThreadAddress = val.toInt();
    if ("MsgType" == key)           data->dMsgType = val.toMsgType();
    if ("BootMsec" == key)          data->dBootMsec = val.toInt();
    if ("TimeString" == key)        data->dTimeString = val;
    if ("BackTrace" == key)         data->dBackTrace = val;
    if ("Function" == key)          data->dFunction = val;
}

// ======== For QSharedDataPointer =======
QtLogFields::QtLogFields()
    : data(new QtLogFieldsData)
{}

QtLogFields::QtLogFields(const QtLogFields &rhs)
    : data{rhs.data}
{}

QtLogFields::QtLogFields(QtLogFields &&rhs)
    : data{std::move(rhs.data)}
{}

QtLogFields &QtLogFields::operator=(const QtLogFields &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

QtLogFields &QtLogFields::operator=(QtLogFields &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

QtLogFields::~QtLogFields() {}
