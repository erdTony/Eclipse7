#include "LogMessage.h"

LogMessage::LogMessage() {;}

LogMessage::LogMessage(QtMsgType type,
                       const QMessageLogContext &context,
                       const QString &msg)
{
    set(msg);
}

void LogMessage::set(const QString &msg)
{
    LogItem tLI;
}
