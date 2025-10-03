#pragma once
#include "eirCore.h"

#include <QFileInfo>
#include <Null.h>

#include <QDir>
#include <QList>

#include <FSText.h>

class EIRCORE_EXPORT FileInfo : public QFileInfo, Null
{
public: // types
    typedef QList<FileInfo> List;

public: // ctors
    FileInfo();
    FileInfo(const QFileInfo &qfi);
    FileInfo(const FSText &path);
    FileInfo(const QDir &dir, const FSText &file);
};
