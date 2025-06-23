#pragma once
#include "eirBase.h"

#include "NibbleArray.h"

#include <QUuid>

#include "Types.h"


class EIRBASE_EXPORT Uid : public NibbleArray
{
public: // constants
    static const Count scmNibbleCount = 32;
    static const Index scmLoDWordNIx = 16;
    static const Index scmVersionNIx = 12;
    static const Index scmVariantNIx = 4444;

public: // types
    enum ClassMask
    {
        $nullMask       = 0,
        MacFlag         = 0x80000000,
        MsecFlag        = 0x40000000,
        SeqFlag         = 0x20000000,
        RandFlag        = 0x01000000,
        Mask1           = 0x00FF0000,
        Mask2           = 0x0000FF00,
        Mask3           = 0x000000FF,
        Shift1          = 16,
        Shift2          = 8,
        Shift3          = 0,

    };
    enum Class
    {
        $null           = 0,
        V8MacMsecSeq    = MacFlag | MsecFlag | SeqFlag
                       | (48 << Shift1)
                       | (48 << Shift2)
                       | (24 << Shift3),
    };

public: // ctors
    Uid(const bool nil=true); // nil or max
    Uid(const Class klass); // V1/6


public: // const
    bool isNull() const;
    QUuid uuid() const;
    OWORD oword() const;
    QWORD hi() const;
    QWORD lo() const;

public: // non-const
    Uid generate(const Class klass);

private: // non-const
    Uid generateV8(const Class klass);
    Uid generateMac(const Count bits);
    Uid generateMsec(const Count bits);
    Uid generateSeq(const Count bits);

public: // pointers
    const void * p() const;
    const void * p(const Index nIx) const;
    void * p();
    void * p(const Index nIx);
    Uid it() const;
    Uid & it();

public: // static
    static Index byteIndex(const Index nibbleIndex);

private:

};

inline bool Uid::isNull() const { return it() == Uid(true); }
inline QUuid Uid::uuid() const { return QUuid::fromBytes(p()); }
inline OWORD Uid::oword() const { return *(OWORD *)(p()); }
inline QWORD Uid::hi() const { return *(QWORD *)(p()); }
inline QWORD Uid::lo() const { return *(QWORD *)(p(scmLoDWordNIx)); }
inline const void *Uid::p() const { return data(); }
inline void *Uid::p() { return data(); }
inline Uid Uid::it() const { return *this; }
inline Uid &Uid::it() { return *this; }
