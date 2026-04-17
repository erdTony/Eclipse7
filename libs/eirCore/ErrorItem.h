#pragma once

#include "Id.h"

class ErrorItem
{
public:
    ErrorItem();

private:
    Id mId;
    AText mFormat;
    QVariantList mVars;
};
