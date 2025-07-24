#include "CTextList.h"

CTextList::CTextList() {}

QStringList CTextList::toStringList() const
{
    QStringList result;
    foreach (const CText cct, it())
        result << cct.toString();
    return result;
}
