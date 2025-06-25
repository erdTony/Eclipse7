#include "KeySeg.h"


KeySeg::KeySeg() {;}
KeySeg::KeySeg(const char *pch) : AText(pch) {;}
KeySeg::KeySeg(const AText &other) : AText(other) {;}
KeySeg::KeySeg(const QString &s) : AText(s) {;}

bool KeySeg::equals(const KeySeg &other) const
{
    return 0 == compare(other);
}

bool KeySeg::isValidFirst(const char ch)
{
    return std::isalpha(ch) || '_' == ch;
}

bool KeySeg::isValidChar(const char ch)
{
    return std::isalnum(ch) || '_' == ch;
}
