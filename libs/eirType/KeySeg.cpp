#include "KeySeg.h"


bool KeySeg::isValidFirst(const char ch)
{
    return std::isalpha(ch) || '_' == ch;
}

bool KeySeg::isValidChar(const char ch)
{
    return std::isalnum(ch) || '_' == ch;
}
