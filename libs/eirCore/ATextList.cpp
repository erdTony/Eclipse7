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


AText ATextList::join(const AText atx) const
{
    ATextList tList = *this;
    AText result = isEmpty() ? AText() : tList.takeFirst();
    while ( ! tList.isEmpty())
    {
        result += atx;
        result += tList.takeFirst();
    }
    return result;
}

ATextList::PairList ATextList::split(const char ch) const
{
    ATextList::PairList result;
    foreach (const AText cATextIn, it())
    {
        const AText::Pair cPair = cATextIn.keyValue(ch);
        result.append(cPair);
    }
    return result;
}

// ---------------------- static -----------------------

ATextList ATextList::toList(const PairList atxlpr, const char assign)
{
    ATextList result;
    foreach (const AText::Pair cAtxp, atxlpr)
    {
        const AText cAtx = cAtxp.first + assign + cAtxp.second;
        result << cAtx;
    }
    return result;
}


ATextList ATextList::toList(const PairMMap atxlMm, const char assign)
{
    ATextList result;
    QMultiMapIterator<AText, AText> mmit(atxlMm);
    while (mmit.hasNext())
    {
        mmit.next();
        const AText cKey = mmit.key();
        const AText cVal = mmit.value();
        const AText cAtx = cKey + assign + cVal;
        result << cAtx;
    }
    return result;
}
