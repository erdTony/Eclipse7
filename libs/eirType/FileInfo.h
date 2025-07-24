#pragma once
#include "eirType.h"


#include <QFileInfo>

class AText;

class EIRTYPE_EXPORT  FileInfo : public QFileInfo
{
public:
    FileInfo();
    FileInfo(const AText *at);
};
