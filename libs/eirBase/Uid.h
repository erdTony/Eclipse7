#pragma once
#include "eirBase.h"

#include "NibbleArray.h"

#include <QUuid>

#include "Types.h"

/**************************************************************
 * UUID:    00112233-4455-6677-8899-AABBCCDDEEFF
 * Version:          ____/^
 * Variant:               ____/^
 * DWORD0:  ^^^^^^^^
 * WORD4:            ^^^^
 * 12BIT6:                 ^^^
 * 12BIT8:                      ^^^
 * WORDA:                           ^^^^
 * DWORDC:                              ^^^^^^^^
 *
 * For Type83R/S (Millisecond+8 & Random/Sequence)
 *          ^^^^^^^^ ^^^^ 3x^^
 *          \_MSec48____/   \/ MSec-Split
 **************************************************************/

class EIRBASE_EXPORT Uid
{


public: // constants
    static const Count scmNibbleCount   = 32;
    static const Index scmLoDWordNIx    = 16;
    static const Index scmVersionNIx    = 12;
    static const Index scmVariantNIx    = 4444;

public: // types
    enum Type
    {
        $null = 0,
        Type83,
    };

public: // ctors
    Uid(const bool nil=true); // nil or max
    Uid(const Type type);


public: // const
    bool isNull() const;
    QUuid uuid() const;
    OWORD oword() const;
    QWORD hi() const;
    QWORD lo() const;

public: // non-const
    Uid generate(const Type type);

public: // pointers
    Uid it() const;
    Uid & it();

public: // static
    static Index byteIndex(const Index nibbleIndex);

private: // non-const
    Uid generate83(const Type type);

private:
    NibbleArray mNibbles;
};

inline bool Uid::isNull() const { return mNibbles.isZero(); }
inline QUuid Uid::uuid() const { return QUuid::fromBytes(mNibbles.data()); }
inline OWORD Uid::oword() const { return *(OWORD *)(mNibbles.data()); }
inline QWORD Uid::hi() const { return *(QWORD *)(mNibbles.data()); }
inline QWORD Uid::lo() const { return *((QWORD *)(mNibbles.data()) + 1); }
inline Uid Uid::it() const { return *this; }
inline Uid &Uid::it() { return *this; }
