#include "BaseLogFormat.h"

BaseLogFormat::BaseLogFormat() {;}
BaseLogFormat::BaseLogFormat(const LogItem &li) : mLogItem(li) {;}

QString BaseLogFormat::string() const
{
    return QString("%1%2 %3,%4 %5 %6")
        .arg(li().level().chr())
        .arg(QDateTime::fromMSecsSinceEpoch(li().timeStamp()).toString("hh:mm:ss.zzz"))
        .arg(li().fileInfo().baseFileName()(), 30)
        .arg(li().fileLine(), +4)
        .arg(li().level().name()(), +12)
        .arg(li().formattedMessage());
}

QStringList BaseLogFormat::stringList() const
{

}

