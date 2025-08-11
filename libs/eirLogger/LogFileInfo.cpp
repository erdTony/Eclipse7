#include "LogFileInfo.h"

LogFileInfo::LogFileInfo() {;}
LogFileInfo::LogFileInfo(const QString &pathname) : QFileInfo(pathname), mSet(true) {;}
LogFileInfo::LogFileInfo(const QDir &dir, const QString &filename) : QFileInfo(dir, filename), mSet(true) {;}
