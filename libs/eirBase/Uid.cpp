#include "Uid.h"

Uid::Uid(const bool nil) : NibbleArray(scmNibbleCount, nil ? 0x0 : 0xF) {;}

Uid::Uid(const Class klass)
{
    switch (klass)
    {
    case V8MacMsecSeq:   generateV8(V8MacMsecSeq);      break;
    }
}

Uid Uid::generate(const Class klass)
{
    return Uid();
}

Uid Uid::generateV8(const Class klass)
{
    return Uid(true);
}

const void *Uid::p(const Index nIx) const
{
    return (BYTE *)(NibbleArray::data()) + byteIndex(nIx);
}

void *Uid::p(const Index nIx)
{
    return (BYTE *)(NibbleArray::data()) + byteIndex(nIx);
}

Index Uid::byteIndex(const Index nibbleIndex)
{
    return nibbleIndex / 2;
}
