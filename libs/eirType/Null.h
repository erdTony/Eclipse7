#pragma once
#include "eirType.h"

#include "TriBool.h"

class EIRTYPE_EXPORT Null : private TriBool
{
public:
    Null();
    Null(const bool is);

public: // const
    bool null() const;

public: // non-const
    bool nullify();
    bool notNull();
};

inline bool Null::null() const { return TriBool::isTrue(); }
