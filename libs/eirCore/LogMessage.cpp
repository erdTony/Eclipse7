#include "LogMessage.h"

LogMessage::LogMessage() {;}

LogMessage::LogMessage(QtMsgType type,
                       const QMessageLogContext &context,
                       const QString &msg)
    : mQtMsgType(type)
    , mFileName(context.file)
    , mFuncName(context.function)
    , mFileLine(context.line)
    , mMessage(msg)
{
    ;
}

bool LogMessage::isNull() const
{
    return mFileName.isEmpty();
}

