#include "AText.h"

#include <QString>

#include <ctype.h>
#include <climits>

#include "ATextList.h"
#include "Types.h"

char AText::smHingeChar = ' ';


AText::List AText::toList(const char ch) const
{
    return ATextList(mid(0).split(ch ? ch : hinge()));
}

AText::Pair AText::pair(const char ch) const
{
    AText tKey, tValue;
    Index ix = indexOf(ch);
    if (ix <= 0)
        tKey = mid(0);
    else if (ix >= length() - 1)
        tKey = mid(0), tValue = "";
    else
        tKey = first(ix -1), tValue = mid(ix + 1);
    return Pair(tKey, tValue);
}

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

AText AText::append(const AText &more)
{
    QByteArray::append(more);
    return it();
}

AText AText::append(const char ch)
{
    QByteArray::append(ch);
    return it();
}

bool AText::isValidFirst(const char ch)
{
    return isprint(ch);
}

bool AText::isValidChar(const char ch)
{
    return isprint(ch);
}
