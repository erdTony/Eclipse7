#include "KeySegList.h"

void KeySegList::set(const AText &at)
{
    clear();
    foreach(const AText cSplitItem, at.split(hinge()))
        append(KeySeg(cSplitItem));
}
