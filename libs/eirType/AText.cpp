#include "AText.h"

#include <ctype.h>


void AText::set(const char *pch)
{
    clear();
    QByteArray::reserve(strlen(pch));
    if (*pch && isValidFirst(*pch))
        QByteArray::append(*pch);
    while (*pch)
    {
        if (isValidChar(*pch))
            QByteArray::append(*pch);
        ++pch;
    }
    QByteArray::append(char(0));
}

bool AText::isValidFirst(const char ch)
{
    return isprint(ch);
}

bool AText::isValidChar(const char ch)
{
    return isprint(ch);
}
