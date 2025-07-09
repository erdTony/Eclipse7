#include "Uid.h"

#include <QtEndian>

#include "MillisecondTime.h"

Uid::Uid(const bool nil) : mNibbles(NibbleArray(scmNibbleCount, nil ? 0x0 : 0xF)) {;}
Uid::Uid(const Type type) { generate(type); }

Uid Uid::generate(const Type type)
{
    Uid result(false);
    switch (type)
    {
    case Type83:   result = generate83(type);     break;
    default:                                      break;
    }
    return result;
}

Uid Uid::generate83(const Type type)
{
    Uid result;
    Milliseconds tCurrentEms = MillisecondTime::current();
    quint64 tNetworkEms = qToBigEndian<quint64>(tCurrentEms);
    //mNibbles.set()
    return result;
}

