#include "KeySegList.h"

QStringList KeySegList::toStringList() const
{
    QStringList result;
    foreach (const KeySeg cSeg, it())
        result << cSeg.toString();
    return result;
}

void KeySegList::set(const AText &at)
{
    clear();
    foreach (const AText cAT, at.split(hinge()))
        append(KeySeg(cAT));
}
