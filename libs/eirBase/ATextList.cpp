#include "ATextList.h"

#include <QString>

//#include "Types.h"

ATextList::ATextList() {;}
ATextList::ATextList(const AText::List &other) : AText::List(other) {;}

ATextList::ATextList(const QByteArrayList &other)
{
    foreach (const QByteArray cBA, other)
        append(AText(cBA));
}

ATextList::ATextList(const QStringList &other)
{
    foreach (const QString cS, other)
        append(AText(cS));
}

ATextList &ATextList::operator =(const AText::List &other)
{
    foreach (const AText cAT, other)
        append(cAT);
    return it();
}


AText ATextList::join(const char ch) const
{
    ATextList tList = *this;
    AText result = isEmpty() ? AText() : tList.takeFirst();
    while ( ! tList.isEmpty())
    {
        result += ch;
        result += tList.takeFirst();
    }
    return result;
}

ATextList::Pair ATextList::split(const char ch) const
{
    ATextList tLtList, tRtList;
    foreach (const AText cTextIn, *this)
    {
        AText::Pair tPair = cTextIn.split(ch);
        tLtList << tPair.first, tRtList << tPair.second;
    }
    return Pair(tLtList, tRtList);
}


