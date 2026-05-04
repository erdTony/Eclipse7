#pragma once
#include "eirCore.h"

#include <QUuid>
#include <QMetaType>

#include <QAnyStringView>
#include <QList>

#include "Key.h"
#include "NetworkMacAddress.h"
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
 *          ^^^^^^^^--SegmentA
 *                   ^^^^--SegmentB
 *                         ^^^--SegmentC
 *                              ^^^-SegmentD
 *                                  ^^^^^^^^^^^^--SegmentE
 */

public: // constants
    static const Count scmNibbleCount   = 32;
    static const Index scmVersionNIx    = 12;
    static const Index scmVariantIx     = 8;
    static const OWORD scmNullValue     = -1;

public: // types
    enum Segment
    {
        $nullSegment = 0,
        SegmentA            = 0x0020, // A=32bits @0    time_low
        SegmentB            = 0x2010, // B=16bits @32   time_mid
        SegmentVer          = 0x3004, // Ver=4bit @48
        SegmentC            = 0x340C, // C=12bits @52   time_hi
        SegmentVar          = 0x4004, // Var=4bit @64
        SegmentD            = 0x440C, // D=12bits @68
        SegmentE            = 0x5030, // D=48bits @80
    };

    enum Variant
    {
        $nullVar    = -1,
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
        VarGuid   = 12,   // 0b110+ (Microsoft)
        VarGuid13,
        $invalidVar = 15
    };
    enum Version            // for VarDce 
    {
        $nullVer            = 0,
        VerGTimeseqNode1    = QUuid::Time,          // 1
        VerSecurity         = QUuid::EmbeddedPOSIX, // 2
        VerTextMd5          = QUuid::Name,          // 3 = QUuid::Md5
        VerRandom           = QUuid::Random,        // 4
        VerTextSha          = QUuid::Sha1,          // 5
        VerGTimeseqNode6    = 6,
        VerUTimeseqRandom   = QUuid::UnixEpoch,     // 7
        VerCustom           = 8, // 60,60
        VerCustom5,         // 9    32,16,12,12,48
        VerCustom4,         // 10   32,16,24,48
        VerCustom3a32,      // 11   32,40,48
        VerCustom3b48,      // 12   48,24,48
        VerCustom2a40,      // 13   32,80
        VerCustom2b60,      // 14   48,72
        VerCustom2c72,      // 15   72,48
        $invalidVer         = QUuid::VerUnknown     // -1
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
    Uid(const bool rand); // nil or random
    Uid(const QAnyStringView & s);
    Uid(const XText & hex);
    Uid(const DWORD dw00, const WORD w08, const WORD w12,
        const WORD w16, const QWORD qw20 /*48bits*/);
    Uid(const Variant var); // NCS or GUID
    Uid(const Version ver); // DCE flavor
    Uid(const Uid &ns, const AText text); // DCEv5
    Uid(const Version ver, const NetworkMacAddress &macOverride); // DCDv6

public: // const
    bool isNull() const;
    bool isNil() const;
    UID qUnion() const;
    bool equals(const Uid &rhs) const;
    bool less(const Uid &rhs) const;
    bool operator == (const Uid &rhs) const;
    bool operator < (const Uid &rhs) const;
    QString toString(const QUuid::StringFormat mode=QUuid::WithBraces) const;
    AText toAtx() const;
    XText toHex() const;
    QWORD segment(const Segment uidseg) const;
    Key toKey() const;
    Key toKey(const KeySeg &prefix) const;
    QString tail() const;
    operator QString () const;
    QUuid uuid() const;
    QWORD hi() const;
    QWORD lo() const;
#ifndef Q_CC_MSVC
    OWORD oword() const;
#endif

public: // non-const
    void hi(const QWORD qw);
    void lo(const QWORD qw);
    void set(const QUuid other);
    void set(const Variant var);
    void set(const Version ver);
    void set(const Index bitOffset, const Count bitCount, const QWORD qw);
    void set(const Segment seg, const QWORD qw);
    Uid generate(const bool rand);
    Uid generate(const Variant var);
    Uid generate(const Version ver);
    Uid generate(const Type type);
    Uid generate1(const NetworkMacAddress &mac=NetworkMacAddress(true));
    Uid generate6(const NetworkMacAddress &mac=NetworkMacAddress(true));
    Uid generate7(const Type type);
    void nullify();
    void nilify();
    void maxify();
    void randomize();

public: // pointers
    UID & ref() const;
    UID & ref();
    Uid it() const;
    Uid & it();

public: // static
    static Uid reference();

private: // const
    XText xtext(const Segment uidseg) const;

private: // non-const
    void insert(Uid &uid, const Uid::Version ver, const SQWORD gtime,
                const WORD seq, const NetworkMacAddress &mac);

private: // static
    static bool isVarNcs(const Variant var);
    static bool isVarGuid(const Variant var);
    static bool isNull(const Segment uidseg);
    static bool isValidSegment(const Segment uidseg);
    static unsigned segmentBitOffset(const Segment uidseg);
    static Count segmentBitLength(const Segment uidseg);
    static OWORD segmentMask(const Segment uidseg);

public: // QMetaType
    Uid() = default;
    ~Uid() = default;
    Uid(const Uid &) = default;
    Uid &operator=(const Uid &) = default;

private:
    UID mUnion = { { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };
};

Q_DECLARE_METATYPE(Uid);


inline UID Uid::qUnion() const { return mUnion; }
inline bool Uid::operator ==(const Uid &rhs) const { return equals(rhs); }
inline bool Uid::operator <(const Uid &rhs) const { return less(rhs); }
inline Key Uid::toKey() const { return toKey("UID:"); }
inline Uid::operator QString() const { return toString(); }
inline Uid Uid::it() const { return *this; }
inline Uid &Uid::it() { return *this; }
