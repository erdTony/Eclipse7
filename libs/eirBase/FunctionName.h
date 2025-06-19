#pragma once
#include "eirBase.h"

#include "AText.h"

class AText;


class EIRBASE_EXPORT FunctionName : public AText
{
public:
    FunctionName();
    FunctionName(const AText &at);
};
