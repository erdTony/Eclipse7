#pragma once

#include <QFileInfo>

class QDir;
class QString;

#include <TriBool.h>

class LogFileInfo : public QFileInfo
{
public:
    LogFileInfo();
    LogFileInfo(const QString &pathname);
    LogFileInfo(const QDir &dir, const QString &filename);

private:
    TriBool mSet;
};
