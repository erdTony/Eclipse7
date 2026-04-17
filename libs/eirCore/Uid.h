#pragma once
#include "eirCore.h"

#include "NibbleArray.h"

#include <QList>
#include <QUuid>

#include "Key.h"
#include "Types.h"
class KeySeg;

class EIRCORE_EXPORT Uid : public QUuid
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
        SegmentNix0811      = 0x00080B04,
        SegmentNix1215      = 0x000C0F04,
        SegmentNix1619      = 0x00101304,
        SegmentNix2031      = 0x00141F0C,
        //                        ^^--Segment Nix Start
        //                          ^^--Segment Nix End
        //                            ^^--Segment Nibble Count
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
        VerGTimeseqNode1    = QUuid::Time,
        VerSecurity         = QUuid::EmbeddedPOSIX,
        VerTextMd5          = QUuid::Name,
        VerRandom           = QUuid::Random,
        VerTextSha          = QUuid::Sha1,
        VerGTimeseqNode6    = 6,
        VerUTimeseqRandom   = QUuid::UnixEpoch,
        VerCustom           = 8, // 60,60
        VerCustom5,         // 9    32,16,12,12,48
        VerCustom4,         // 10   32,16,24,48
        VerCustom3a32,      // 11   32,40,48
        VerCustom3b48,      // 12   48,24,48
        VerCustom2a40,      // 13   32,80
        VerCustom2b60,      // 14   48,72
        VerCustom2b72,      // 15   72,48
        $invalidVer         = QUuid::VerUnknown
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
    Uid(const QString & s);
    Uid(const XText & hex);
    Uid(const DWORD dw00, const WORD w08, const WORD w12,
        const WORD w16, const QWORD qw20 /*48bits*/);
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
    QString toString(const QUuid::StringFormat mode=QUuid::WithBraces) const;
    QWORD segment(const Segment uidseg);
    Key toKey() const { return toKey("URL"); }
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
    void set(const QUuid other);
    void set(const Segment seg, const QWORD qw);
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
    static Uid reference();
    static Index byteIndex(const Index nibbleIndex);
    static Index nixBegin(const Segment uidseg);
    static Index nixEnd(const Segment uidseg);
    static Count nibbleCount(const Segment uidseg);

private: // const
    XText xtext(const Segment uidseg) const;

private: // non-const
    Uid generate7(const Type type);

private: // static
    static bool isNull(const Segment uidseg);
    static OWORD mask(const Segment uidseg);

private:
};



inline bool Uid::operator ==(const Uid &rhs) const { return equals(rhs); }
inline bool Uid::operator <(const Uid &rhs) const { return less(rhs); }
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
