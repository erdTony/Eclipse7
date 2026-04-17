#include "Uid.h"

#include <QtEndian>
#include <QRandomGenerator>

#include "../../../doctest/doctest/doctest.h"

#include "KeySeg.h"
#include "MillisecondTime.h"

Uid::Uid() {;}
Uid::Uid(const bool nil) : mNibbles(NibbleArray(scmNibbleCount, nil ? 0x0 : 0xF)) {;}

Uid::Uid(const QString &s) :
Uid::Uid(const Version ver) { generate(ver); }


bool Uid::isNull() const { return mNibbles.isNull(); }

bool Uid::isNil() const { return mNibbles.isZero(); }

bool Uid::equals(const Uid &rhs) const
{
#ifdef Q_CC_MSVC
    return hi() == rhs.hi() && lo() == rhs.lo();
#else
    return oword() == rhs.oword();
#endif
}

bool Uid::less(const Uid &rhs) const
{
#ifdef Q_CC_MSVC
    return (hi() == rhs.hi()) ? (lo() < rhs.lo()) : (hi() < rhs.hi());
#else
    return oword() < rhs.oword();
#endif
}

QString Uid::toString(const QUuid::StringFormat mode) const
{
    return uuid().toString(mode);
}

Key Uid::toKey(const KeySeg &prefix) const
{
    Key result = prefix;
    result.append(toString(QUuid::WithoutBraces).replace('-', Key::hinge()));
    return result;
}

QString Uid::tail() const
{
    return toString().right(14);
}

void Uid::hi(const QWORD qw)
{
    QWORD * pQW = (QWORD *)mNibbles.data();
    memcpy(pQW, &qw, sizeof(qw));
}

void Uid::lo(const QWORD qw)
{
    QWORD * pQW = (QWORD *)mNibbles.data(scmNibbleCount / 2);
    memcpy(pQW, &qw, sizeof(qw));
}

void Uid::set(const Segment seg, const QWORD qw)
{
    OWORD m = mask(seg);
    OWORD ow = qw;
    ow &= m;
    ow <<= (scmNibbleCount - nixEnd(seg)) * 4;
    OWORD * p = (OWORD *)mNibbles.data();
    *p &= ~ m;
    *p |= ow;
}

void Uid::set(const Version ver)
{
    mNibbles.set(scmVersionNIx, ver);
}

Uid Uid::generate(const bool nil)
{
    Uid result;
    if (nil)
        result.mNibbles.fill(0, scmNibbleCount);
    else
        result.randomize();
    return result;
}

Uid Uid::generate(const Version ver)
{
    Uid result(true);
    // TODO fill nibbles random
    result.set(ver);
    return result;
}

void Uid::randomize()
{
    lo(QRandomGenerator::global()->generate64());
    hi(QRandomGenerator::global()->generate64());
}

Uid Uid::reference()
{
    Uid result(true); // nil
    result.set(SegmentA, 0x01234567);
    result.set(SegmentB, 0x89AB);
    result.set(SegmentC, 0xCDEF);
    result.set(SegmentD, 0x0123);
    result.set(SegmentE, 0x456789ABCDEF);
    return result;
}

Index Uid::byteIndex(const Index nibbleIndex)
{
    return 2 * nibbleIndex;
}

Index Uid::nixBegin(const Segment uidseg)
{
    return (uidseg & 0x00FF0000) >> 16;
}

Index Uid::nixEnd(const Segment uidseg)
{
    return (uidseg & 0x0000FF00) >> 8;
}

Count Uid::nibbleCount(const Segment uidseg)
{
    return uidseg & 0x000000FF;
}

XText Uid::xtext(const Segment uidseg) const
{
    const NibbleArray cNA = mNibbles.segment(nixBegin(uidseg),
                                             nibbleCount(uidseg));
    return cNA.toHex();
}

bool Uid::isNull(const Segment uidseg)
{
    return uidseg == $nullSegment;
}

OWORD Uid::mask(const Segment uidseg)
{
    return ((OWORD)1 << (nibbleCount(uidseg) * 4)) - (OWORD)1;
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


