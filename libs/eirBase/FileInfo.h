#pragma once
#include "eirBase.h"


#include <QFileInfo>

class AText;

class EIRBASE_EXPORT  FileInfo : public QFileInfo
{
public:
    FileInfo();
    FileInfo(const AText *at);
};
