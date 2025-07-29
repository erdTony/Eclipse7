#pragma once
#include "eirType.h"

class EIRTYPE_EXPORT TriBool
{
public: // ctors
    TriBool();
    TriBool(const bool is);

public: // const
    bool isTrue() const;
    bool isFalse() const;
    bool isNull() const;
    bool isInvalid() const;
    bool value() const;
    bool valid() const;

public: // non-const
    void set(const bool is=true);
    void reset();
    void nullify();
    void invalidate();

private:
    bool mValue = false;
    bool mValid = false;
};

inline bool TriBool::value() const { return mValue; }
inline bool TriBool::valid() const { return mValid; }
