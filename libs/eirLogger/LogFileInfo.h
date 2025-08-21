#pragma once
#include "eirLogger.h"

#include <QFileInfo>

class QDir;
class QString;

#include <FSText.h>
#include <FSTextList.h>
#include <TriBool.h>

class EIRLOGGER_EXPORT LogFileInfo : private QFileInfo
{
public:
    LogFileInfo();
    LogFileInfo(const QString &pathname);
    LogFileInfo(const QDir &dir, const QString &filename);

public: // const
    FSText filePath() const;
    FSText baseFileName() const;
    FSTextList pathList() const;

private:
    TriBool mSet;
};

