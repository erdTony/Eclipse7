#include "Key.h"


QWORD Key::hash64() const
{
    QWORD result = 0;
    KeySegList tSegments = it();
    Index tPosition = 3;
    while (tSegments.notEmpty())
    {
        const KeySeg tSeg = tSegments.takeLast();
        const WORD tHash16 = tSeg.hash16();
    }
    return result;
}
