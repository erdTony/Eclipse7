#include "NAText.h"

NAText::NAText() {}
NAText::NAText(const char *pch) : AText(pch) {;}
NAText::NAText(const QByteArray &ba) : AText(ba) {;}
NAText::NAText(const QString &s) : AText(s) {;}

XText NAText::toXText() const
{
    return XText(it());
}

bool NAText::isValidFirst(const char ch)
{
    return isxdigit(ch);
}

bool NAText::isValidChar(const char ch)
{
    return isxdigit(ch) || AText("-:").contains(ch);
}
