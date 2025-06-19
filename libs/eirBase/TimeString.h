#pragma once
#include "eirBase.h"

#include "AText.h"

class AText;


class EIRBASE_EXPORT TimeString : public AText
{
public:
    TimeString();
    TimeString(const AText &at);
};
