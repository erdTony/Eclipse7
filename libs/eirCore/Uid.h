#pragma once
#include "eirCore.h"

#include "NibbleArray.h"

#include <QList>
#include <QUuid>

#include "Key.h"
#include "Types.h"
class KeySeg;

class EIRCORE_EXPORT Uid
{
/*
 * UUID:    01234567-89AB-CDEF-0123-456789ABCDEF
 *          00000000 0011 1111 1111 222222222233
 * Hex Nix: 01234567 89AB CDEF 0123 456789ABCDEF
 * Dec Nix: 01234567 8901 2345 6789 012345678901
 *                   Ver--^    ^--Var
 */
public: // constants
    static const Count scmNibbleCount   = 32;
    static const Index scmVersionNIx    = 12;
    static const Index scmVariantNIx    = 16;

public: // types
    enum Segment
    {
        $nullSegment = 0,
        SegmentNix0007      = 0x00000708,
        SegmentNix0811      = 0x00081104,
        SegmentNix1215      = 0x00121504,
        SegmentNix1619      = 0x00161904,
        SegmentNix2031      = 0x0020310C,
        SegmentA            = SegmentNix0007,
        SegmentB            = SegmentNix0811,
        SegmentC            = SegmentNix1215,
        SegmentD            = SegmentNix1619,
        SegmentE            = SegmentNix2031,
    };

    enum Variant
    {
        VarNcs      = 0,    // 0b0--+
        VarNcs1,
        VarNcs2,
        VarNcs3,
        VarNcs4,
        VarNcs5,
        VarNcs6,
        VarNcs7,
        VarDce      = 8,    // 0b10-+
        VarDce9,
        VarDce10,
        VarDce11,
        VarGuid     = 12,   // 0b110+ (Microsoft)
        VarGuid13,
        $nullVar    = 14,
        $invalidVar = 15
    };
    enum Version            // for VarDce 
    {
        $nullVer            = 0,
        VerGTime1SeqNode    = 1,
        VerSecurity         = 2,
        VerNsTextMd5        = 3,
        VerRandom           = 4,
        VerNsTextSha        = 5,
        VerGTime6SeqNode    = 6,
        VerUTimeSeqRandom   = 7,
        VerCustom           = 8,
        VerCustom9,
        VerCustom10,
        VerCustom11,
        VerCustom12,
        VerCustom13,
        VerCustom14,
        $invalidVer        = 15
    };
    enum Class              // for VerCustom (8)
    {
        $nullClass = 0,
        ClassA,
    };
    enum Type
    {
        $nullType = 0,
        Log,
    };
    typedef QList<Uid> List;

public: // ctors
    Uid(); // null
    Uid(const bool nil); // nil or random
    Uid(const Variant var); // NCS or GUID
    Uid(const Version ver); // DCE flavor
    Uid(const Uid &ns, const AText text); // DCEv5
    Uid(const QByteArray &macOverride); // DCDv6

public: // const
    bool isNull() const;
    bool isNil() const;
    bool equals(const Uid &rhs) const;
    bool less(const Uid &rhs) const;
    bool operator == (const Uid &rhs) const;
    bool operator < (const Uid &rhs) const;
    QString toString() const;
    Key toKey() const;
    Key toKey(const KeySeg &prefix) const;

    QString tail() const;
    operator QString () const;
    QUuid uuid() const;
#ifndef Q_CC_MSVC
    OWORD oword() const;
#endif
    QWORD hi() const;
    QWORD lo() const;

public: // non-const
    void hi(const QWORD qw);
    void lo(const QWORD qw);
    void set(const Version ver);
    Uid generate(const bool nil);
    Uid generate(const Version ver);
    Uid generate(const Type type);
    void nullify();
    void randomize();

public: // pointers
    Uid it() const;
    Uid & it();

public: // static
    static Index byteIndex(const Index nibbleIndex);
    static Index nixBegin(const Segment uidseg);
    static Index nixEnd(const Segment uidseg);
    static Count nixCount(const Segment uidseg);

private: // const
    XText xtext(const Segment uidseg) const;

private: // non-const
    Uid generate7(const Type type);

private:
    NibbleArray mNibbles;
};

inline bool Uid::isNull() const { return mNibbles.isNull(); }
inline bool Uid::isNil() const { return mNibbles.isZero(); }
inline bool Uid::operator ==(const Uid &rhs) const { return equals(rhs); }
inline bool Uid::operator <(const Uid &rhs) const { return less(rhs); }
inline Key Uid::toKey() const { return toKey("URL"); }
inline Uid::operator QString() const { return toString(); }
inline QUuid Uid::uuid() const { return QUuid::fromBytes(mNibbles.data()); }
#ifndef Q_CC_MSVC
inline OWORD Uid::oword() const { return *(OWORD *)(mNibbles.data()); }
#endif
inline QWORD Uid::hi() const { return *(QWORD *)(mNibbles.data()); }
inline QWORD Uid::lo() const { return *((QWORD *)(mNibbles.data()) + 1); }
inline void Uid::nullify() { mNibbles.clear(); }
inline Uid Uid::it() const { return *this; }
inline Uid &Uid::it() { return *this; }
