#include "CTextList.h"

CTextList::CTextList() {;}
CTextList::CTextList(const QList<CText> other) : CText::List(other) {;}

CText CTextList::join(char ch) const
{
    if (0 == ch) ch = CText::hinge();
    CTextList tList = *this;
    CText result = isEmpty() ? CText() : tList.takeFirst();
    while ( ! tList.isEmpty())
    {
        result.removeLast(); // take off NUL from previous string
        result += ch;
        result += tList.takeFirst();
    }
    return result;
}


QStringList CTextList::toStringList() const
{
    QStringList result;
    foreach (const CText cct, it())
        result << cct.toString();
    return result;
}
