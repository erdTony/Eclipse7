#include "Uid.h"

#include <QtEndian>
#include <QRandomGenerator>

#include "../../../doctest/doctest/doctest.h"

#include "KeySeg.h"
#include "MillisecondTime.h"

Uid::Uid() {;}
Uid::Uid(const bool nil) { nil ? randomize() : nilify(); }
Uid::Uid(const Version ver) { generate(ver); }

bool Uid::isNull() const
{
    return 0 == mUnion.data128[0];
}

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

QUuid Uid::uuid() const
{
    return QUuid(mUnion);
}

QWORD Uid::hi() const
{
    return mUnion.data64[0];
}

QWORD Uid::lo() const
{
    return mUnion.data64[1];
}

#ifndef Q_CC_MSVC
OWORD Uid::oword() const
{
    return mUnion.data128[0];
}
#endif

void Uid::hi(const QWORD qw)
{
    mUnion.data64[0] = qw;
}

void Uid::lo(const QWORD qw)
{
    mUnion.data64[1] = qw;
}

void Uid::segment(const Segment seg, const OWORD ow)
{
    const unsigned cBitOffset = segmentBitOffset(seg);
    const OWORD cBitMask = segmentMask(seg);
    const OWORD cValue = (ow << cBitOffset) & cBitMask;
    mUnion.data128[0] = mUnion.data128[0] & ( ~ cBitMask);
    mUnion.data128[0] = mUnion.data128[0] | cValue;
}

void Uid::set(const Version ver)
{
    Q_ASSERT(!"not done");
}

Uid Uid::generate(const bool nil)
{
    Uid result;
    Q_ASSERT(!"not done");
    return result;
}

Uid Uid::generate(const Version ver)
{
    Uid result(true);
    Q_ASSERT(!"not done");
    return result;
}

void Uid::nullify()
{
    mUnion.data128[0] = 0;
}

void Uid::nilify()
{
    mUnion.data128[0] = 0;
}

void Uid::randomize()
{
    lo(QRandomGenerator::global()->generate64());
    hi(QRandomGenerator::global()->generate64());
}

Uid Uid::reference()
{
#if 1
    Uid result("{01234567-89AB-CDEF-0123-4567890ABCDEF}");
#else
    Uid result(true); // nil
    result.set(SegmentA, 0x01234567);
    result.set(SegmentB, 0x89AB);
    result.set(SegmentC, 0xCDEF);
    result.set(SegmentD, 0x0123);
    result.set(SegmentE, 0x456789ABCDEF);
#endif
    return result;
}

XText Uid::xtext(const Segment uidseg) const
{
    Q_ASSERT(!"not done");
}

bool Uid::isNull(const Segment uidseg)
{
    return $nullSegment == uidseg;
}

bool Uid::isValidSegment(const Segment uidseg)
{
    switch (uidseg)
    {
    case $nullSegment:          return false;

    case SegmentA:
    case SegmentB:
    case SegmentC:
    case SegmentD:
    case SegmentE:              return true;

    case SegmentVar:
    case SegmentVer:            return true;

    default:                    return false;
    }
}

unsigned Uid::segmentBitOffset(const Segment uidseg)
{
    unsigned result = 0;
    if (isValidSegment(uidseg))
        result = (uidseg & 0xFF00) >> 8;
    return result;
}

Count Uid::segmentBitLength(const Segment uidseg)
{
    int result = -1;
    if (isValidSegment(uidseg))
        result = uidseg & 0x00FF;
    return result;
}

OWORD Uid::segmentMask(const Segment uidseg)
{
    OWORD result = -1;
    if (isValidSegment(uidseg))
    {
        result = (1LL << segmentBitLength(uidseg)) - 1;
        result <<= segmentBitOffset(uidseg);
    }
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
