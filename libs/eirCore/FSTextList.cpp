#include "FSTextList.h"

#include "ATextList.h"

FSTextList::FSTextList() {;}
FSTextList::FSTextList(const QByteArrayList &bal) { set(bal); }
FSTextList::FSTextList(const FSText s, const char hinge) { split(s, hinge); }

FSTextList &FSTextList::operator =(const ATextList &atl)
{
    foreach (const AText at, atl)
        append(FSText(at));
    return it();
}

void FSTextList::set(const QByteArrayList &bal)
{
    clear();
    foreach (const QByteArray cBA, bal)
        append(FSText(cBA));
}

void FSTextList::split(const FSText s, char hinge)
{
    char tHinge = hinge ? hinge : FSText::hinge();
    it() = ATextList(s.split(tHinge));
}
