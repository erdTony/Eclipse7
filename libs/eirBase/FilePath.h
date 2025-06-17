#pragma once

#include "AText.h"

class AText;

class FilePath : public AText
{
public:
    FilePath();
    FilePath(const AText &at);
};
