#pragma once

#include <QFileInfo>

class AText;

class FileInfo : public QFileInfo
{
public:
    FileInfo();
    FileInfo(const AText *at);
};
