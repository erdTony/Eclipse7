#include "FSText.h"

#include <ctype.h>

char FSText::smHingeChar = '/';

FSText::FSText() {;}
FSText::FSText(const char *pch) : AText(pch) {;}
FSText::FSText(const QByteArray &ba) : AText(ba) {;}
FSText::FSText(const QString &s) : AText(s) {;}

bool FSText::isValidFirst(const char ch) const
{
    return isValidChar(ch);
}

bool FSText::isValidChar(const char ch) const
{
    return isupper(ch) || islower(ch) || isdigit(ch)
           || AText("-./_\\:").contains(ch);
}
