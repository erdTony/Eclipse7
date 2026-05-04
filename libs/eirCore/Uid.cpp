#include "Uid.h"

#include <QtEndian>
#include <QRandomGenerator>

#include "../../../doctest/doctest/doctest.h"

#include "KeySeg.h"
#include "NanosecondTime.h"
#include "RandomGenerator.h"

Uid::Uid(const bool rand) { generate(rand); }
Uid::Uid(const Variant var) { generate(var); }
Uid::Uid(const Version ver) { generate(ver); }

bool Uid::isNull() const
{
    return scmNullValue == mUnion.data128[0];
}

bool Uid::isNil() const
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

QWORD Uid::segment(const Segment uidseg) const
{
    QWORD result = 0;
    if (isValidSegment(uidseg))
    {
        OWORD tOW = mUnion.data128[0];
        tOW &= segmentMask(uidseg);
        tOW >>= segmentBitOffset(uidseg);
        result = QWORD(tOW);
    }
    return result;
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

void Uid::set(const QUuid other)
{
    mUnion.data128[0] = other.toBytes(QSysInfo::BigEndian).data128[0];
}

void Uid::set(const Variant var)
{
    mUnion.data[8] &= 0x0F;
    mUnion.data[8] |= ((BYTE)var) << 4;
}

void Uid::set(const Version ver)
{
    mUnion.data[6] &= 0x0F;
    mUnion.data[6] |= ((BYTE)ver) << 4;
}

void Uid::set(const Index bitOffset, const Count bitCount, const QWORD qw)
{
    OWORD tMask = ((1LL << bitCount) - 1) << bitOffset;
    OWORD tValue = qw;
    mUnion.data128[0] = mUnion.data128[0] & ( ~ tMask);
    mUnion.data128[0] = mUnion.data128[0] | ((tValue << bitCount) & ( ~ tMask));
}

void Uid::set(const Segment seg, const QWORD qw)
{
    const Index cBitOffset = segmentBitOffset(seg);
    const Count cBitCount = segmentBitLength(seg);
    set(cBitOffset, cBitCount, qw);
}

Uid Uid::generate(const bool rand)
{
    if (rand)
        randomize();
    else
        nilify();
    return it();
}

Uid Uid::generate(const Variant var)
{
    Uid result;
    if (isVarNcs(var) || isVarGuid(var))
    {
        result.randomize();
        result.set(var);
    }
    return it() = result;
}

Uid Uid::generate(const Version ver)
{
    Uid result(true);
    switch (ver)
    {
    case VerGTimeseqNode1:      result.generate1();     break;
    case $nullVer:              result.nilify();        break;
    case $invalidVer:           result.nullify();       break;
    };
    result.set(VarDce);
    result.set(ver);
    return result;
}

Uid Uid::generate1(const NetworkMacAddress &mac)
{

}

Uid Uid::generate6(const NetworkMacAddress &mac)
{

}

void Uid::nullify()
{
    mUnion.data128[0] = scmNullValue;
}

void Uid::nilify()
{
    mUnion.data128[0] = 0;
}

void Uid::maxify()
{
    nilify();
    mUnion.data128[0] = ~ mUnion.data128[0];
}

void Uid::randomize()
{
    lo(QRandomGenerator::global()->generate64());
    hi(QRandomGenerator::global()->generate64());
}

Uid Uid::reference()
{
#if 0
    Uid result("{01234567-89AB-CDEF-0123-4567890ABCDEF}");
#else
    Uid result(false); // nil
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
    XText result;
    if (isValidSegment(uidseg))
    {
        const QWORD cQW = segment(uidseg);
        result.set(&cQW, segmentBitLength(uidseg) / 8);
    }
    return result;
}

void Uid::insert(Uid &uid, const Uid::Version ver, const SQWORD gtime,
                 const WORD seq, const NetworkMacAddress &mac)
{
    switch (ver)
    {
    case VerGTimeseqNode1:
        uid.set(SegmentA,  gtime & 0x00000000FFFFFFFF);
        uid.set(SegmentB, (gtime & 0x0000FFFF00000000) >> 32);
        uid.set(SegmentC, (gtime & 0x0FFF000000000000) >> 48);
        break;
    case VerGTimeseqNode6:
        uid.set(SegmentA, (gtime & 0x00FFFFFFF0000000) >> 28);
        uid.set(SegmentB, (gtime & 0x000000000FFFF000) >> 12);
        uid.set(SegmentC,  gtime & 0x0000000000000FFF);
        break;
    default:
        break;
    }
    uid.set(SegmentD, (seq & 0x0FFF0000) >> 16);
    uid.set(SegmentE, ((seq & 0x0000FFFF) << 24)
                          | (mac.u48() & 0x00FFFFFF));
}

bool Uid::isVarNcs(const Variant var)
{
    return var >= VarNcs && var <= VarNcs7;
}

bool Uid::isVarGuid(const Variant var)
{
    return var >= VarGuid && var <= VarGuid13;
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




