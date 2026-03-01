#pragma once
#include "eirCore.h"


#include "Types.h"

class EIRCORE_EXPORT Iota : public UIntList
{
public: // ctors
    Iota() { set(); }
    Iota(const Count k) { set(k); }
    Iota(const Count k, const unsigned org) { set(k, org); }
    Iota(const Count k, const unsigned org, const unsigned delta) { set(k, org, delta); }

public: // const

public: // non-const
    void set();
    void set(const Count k);
    void set(const Count k, const unsigned org);
    void set(const Count k, const unsigned org, const unsigned delta);

};
