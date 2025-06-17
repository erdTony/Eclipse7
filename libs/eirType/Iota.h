#pragma once
#include "eirtype.h"


#include <Types.h>

class EIRTYPE_EXPORT Iota : public IntList
{
public: // ctors
    Iota() { set(); }
    Iota(const Count k) { set(k); }
    Iota(const Count k, const signed org) { set(k, org); }
    Iota(const Count k, const signed org, const signed delta) { set(k, org, delta); }

public: // const

public: // non-const
    void set();
    void set(const Count k);
    void set(const Count k, const signed org);
    void set(const Count k, const signed org, const signed delta);

};
