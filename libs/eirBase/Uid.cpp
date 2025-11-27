#include "Uid.h"

#include <QtEndian>
#include <QRandomGenerator>

#include "MillisecondTime.h"

Uid::Uid() {;}
Uid::Uid(const bool nil) : mNibbles(NibbleArray(scmNibbleCount, nil ? 0x0 : 0xF)) {;}
Uid::Uid(const Version ver) { generate(ver); }

bool Uid::operator == (const Uid &rhs) const
{
#ifdef Q_CC_MSVC
    return hi() == rhs.hi() && lo() == rhs.lo();
#else
    return oword() == rhs.oword();
#endif
}

bool Uid::operator < (const Uid &rhs) const
{
#ifdef Q_CC_MSVC
    return (hi() == rhs.hi()) ? (lo() < rhs.lo()) : (hi() < rhs.hi());
#else
    return oword() < rhs.oword();
#endif
}

QString Uid::toString() const
{
    return uuid().toString();
}

QString Uid::tail() const
{
    return toString().right(14);
}

void Uid::set(const Version ver)
{
    mNibbles.set(scmVersionNIx, ver);
}

Uid Uid::generate(const Version ver)
{
    Uid result(true);
    // TODO fill nibbles random
    result,set(ver);
    return result;
}
/*
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
*/


