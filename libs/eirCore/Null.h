#pragma once
#include "eirCore.h"

#include "TriBool.h"

class EIRCORE_EXPORT Null : private TriBool
{
public:
    Null();
    Null(const bool is);

public: // const
    bool null() const;

public: // non-const
//    bool set(const bool is);
    bool nullify();
    bool full();
};

inline bool Null::null() const { return TriBool::isTrue(); }
