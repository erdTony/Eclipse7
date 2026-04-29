#include "AText.h"

#include <QString>

#include <ctype.h>
#include <climits>

#include "ATextList.h"
#include "Types.h"

char AText::smHingeChar = ' ';

AText::AText() { clear(); }
AText::AText(const char ch) { set(ch); }
AText::AText(const char *pch) { set(pch); }
AText::AText(const QByteArray &ba) { set(ba); }
AText::AText(const QString &s) { set(s); }
AText::AText(const Count k, const char ch) { set(k, ch); }

AText::List AText::toList(const char ch) const
{
    return ATextList(mid(0).split(ch ? ch : hinge()));
}

AText::Pair AText::keyValue(const char ch) const
{
    AText tKey, tValue;
    Index ix = indexOf(ch);
    if (ix <= 0)
        tKey = mid(0);
    else if (ix >= length() - 1)
        tKey = mid(0), tValue = "";
    else
        tKey = first(ix - 1), tValue = mid(ix + 1);
    return Pair(tKey, tValue);
}


bool AText::isEmpty() const
{
    bool result = QByteArray::isEmpty();
    if ( ! result) result |= QByteArray::at(0) == '\0';
    return result;
}

bool AText::isValid(const Index ix)
{
    return ix >= 0 && ix < length();
}

AText AText::at(const IndexList ixs)
{
    AText result;
    foreach (const Index ix, ixs)
        if (isValid(ix))
            result += QByteArray::at(ix);
    return result;
}

bool AText::equals(const AText &rhs)
{
    QByteArray lhsBA = QByteArray(it());
    QByteArray rhsBA = QByteArray(rhs);
    return lhsBA == rhsBA;
}

void AText::set(const char ch)
{
    clear();
    QByteArray::append(isValidChar(ch) ? ch : '~');
}

void AText::set(const char *pch)
{
    clear();
    if (0 != *pch)
    {
        QByteArray::reserve(strlen(pch) + 1);
        if (*pch && isValidFirst(*pch))
            QByteArray::append(*pch);
        ++pch;
        while (*pch)
        {
            if (isValidChar(*pch))
                QByteArray::append(*pch);
            ++pch;
        }
    }
    QByteArray::append(char(0));
}

void AText::set(const Count k, const char ch)
{
    fill(ch, k);
}

int AText::vprintf(const char *format, va_list vlist)
{
    const Count k = vsnprintf(NULL, 0, format, vlist);
    resize(k);
    return vsnprintf(data(), k, format, vlist);
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

bool AText::isValidFirst(const char ch) const
{
    return isprint(ch);
}

bool AText::isValidChar(const char ch) const
{
    return isprint(ch);
}
