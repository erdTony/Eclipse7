#include "FSTextList.h"

#include "ATextList.h"

FSTextList::FSTextList() {;}
FSTextList::FSTextList(const FSText s, const char hinge) { split(s, hinge); }

FSTextList &FSTextList::operator =(const ATextList &atl)
{
    foreach (const AText at, atl)
        append(FSText(at));
    return it();
}

void FSTextList::split(const FSText s, const char hinge)
{
    it() = ATextList(s.split(hinge));
}
