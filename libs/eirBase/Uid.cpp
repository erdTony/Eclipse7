#include "Uid.h"

#include <QtEndian>
#include <QRandomGenerator>

#include "MillisecondTime.h"

Uid::Uid(const bool nil) : mNibbles(NibbleArray(scmNibbleCount, nil ? 0x0 : 0xF)) {;}
Uid::Uid(const Type type) { generate(type); }

Uid Uid::generate(const Type type)
{
    Uid result(false);
    switch (type)
    {
    case Type7:     result = generate7(type);   break;
    default:                                    break;
    }
    return result;
}

Uid Uid::generate7(const Type type)
{
    Q_UNUSED(type);
    Uid result;
    Milliseconds tCurrentEms = MillisecondTime::current();
    QRandomGenerator tRG(tCurrentEms);
    quint64 tNetworkEms = qToBigEndian<quint64>(tCurrentEms);
    const BYTE cVersion = 7;
    const BYTE cVariant = 8;
    const quint16 cRandom7A = tRG.generate();
    const quint64 cRandom7B = tRG.generate64();
    mNibbles.set( 0, 12, ((BYTE *)(&tNetworkEms)) + 8);
    mNibbles.set(12,  1, &cVersion);
    mNibbles.set(16,  1, &cVariant);
    mNibbles.set(13,  3, (BYTE *)&cRandom7A);
    mNibbles.set(17, 15, (BYTE *)&cRandom7B);
    return result;
}

