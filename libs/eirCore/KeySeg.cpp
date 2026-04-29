#include "KeySeg.h"


KeySeg::KeySeg() {;}
KeySeg::KeySeg(const char ca[]) : AText(ca) {;}
KeySeg::KeySeg(const AText &other) : AText(other) {;}
KeySeg::KeySeg(const QString &s) : AText(s) {;}

bool KeySeg::equals(const KeySeg &other) const
{
    return 0 == compare(other);
}

WORD KeySeg::hash16() const
{
    return 0xFFFF & qHash((QByteArray)(*this), smHashSeed());
}

bool KeySeg::isValidFirst(const char ch) const
{
    return std::isalpha(ch) || '_' == ch;
}

bool KeySeg::isValidChar(const char ch) const
{
    return std::isalnum(ch) || '_' == ch;
}

Seed KeySeg::smHashSeed()
{
    return 0xE16C186C08032010;
}
