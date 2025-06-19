#pragma once
#include "eirBase.h"

#include "AText.h"


class EIRBASE_EXPORT FilePath : public AText
{
public:
    FilePath();
    FilePath(const AText &at);
};
