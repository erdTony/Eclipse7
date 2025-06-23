#include "CText.h"

#include <ctype.h>

char CText::smHingeChar = ' ';

CText::CText() {;}
CText::CText(const char *pch) : AText(pch) {;}
CText::CText(const QByteArray &ba) : AText(ba) {;}
CText::CText(const QString &s) : AText(s) {;}

bool CText::isValidFirst(const char ch)
{
    return isupper(ch) || islower(ch);
}

bool CText::isValidChar(const char ch)
{
    return isupper(ch) || islower(ch) || isdigit(ch);
}
