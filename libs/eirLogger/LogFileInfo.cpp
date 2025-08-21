#include "LogFileInfo.h"

LogFileInfo::LogFileInfo() {;}
LogFileInfo::LogFileInfo(const QString &pathname) : QFileInfo(pathname), mSet(true) {;}
LogFileInfo::LogFileInfo(const QDir &dir, const QString &filename) : QFileInfo(dir, filename), mSet(true) {;}

FSText LogFileInfo::filePath() const
{
    FSText result;
    if (mSet) result = QFileInfo::filePath();
    return result;
}

FSText LogFileInfo::baseFileName() const
{
    FSText result;
    if (mSet) result = QFileInfo::baseName();
    return result;
}

FSTextList LogFileInfo::pathList() const
{
    return filePath().split('/');
}
