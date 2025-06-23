#include "Uid.h"

Uid::Uid(const bool nil) : NibbleArray(scmNibbleCount, nil ? 0x0 : 0xF) {;}
Uid::Uid(const Class klass) { generate(klass); }

Uid Uid::generate(const Class klass)
{
    Uid result(false);
    switch (klass)
    {
    case V8MacMsecSeq:   result = generateV8(V8MacMsecSeq);     break;
    default:                                                    break;
    }
    return result;
}

Uid Uid::generateV8(const Class klass)
{
    Q_UNUSED(klass);
    // TODO
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
