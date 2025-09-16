#pragma once
#include "eirMatgeo.h"

#include <Types.h>

class EIRMATGEO_EXPORT Binary
{
public:
    enum Round { $null = 0, down, closest, up};
    typedef QPair<OWORD, QString> ValueMod;

public:
    Binary();
    Binary(const OWORD val, const Round r=$null);

public: // const
    BYTE power() const;
    OWORD value() const;

public: // non-const
    void set(const OWORD val, Round r=$null);
    void power(const BYTE pow);
    void value(OWORD val);
    Binary predecrement();
    Binary preincrement();
    Binary operator -- ();
    Binary operator ++ ();

public: // static
    static Round round();
    static void round(const Round r);
    static unsigned rounded(const unsigned uval);

private: // pointers
    Binary it() const;
    Binary & it();

private:
    static Round smRound;
    BYTE mPower = 0;
    OWORD mValue = 1 << mPower;
};

inline BYTE Binary::power() const { return mPower; }
inline OWORD Binary::value() const { return mValue; }
inline Binary Binary::operator --() { return predecrement(); }
inline Binary Binary::operator ++() { return preincrement(); }
inline Binary::Round Binary::round() { return smRound; }
inline void Binary::round(const Round r) { smRound = r; }
inline Binary Binary::it() const { return *this; }
inline Binary &Binary::it() { return *this; }
