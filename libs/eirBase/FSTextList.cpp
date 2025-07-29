#include "FSTextList.h"

#include "ATextList.h"
#include "FileSysInfo.h"

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
    char sep = hinge;
    if (0 == sep)
    {
        const FileSysInfo cFSI;
        sep = cFSI.fileSegmentSeparator();
    }
    it() = ATextList(s.split(sep));
}
