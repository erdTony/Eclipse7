#pragma once
#include "eirBase.h"

class EIRBASE_EXPORT TriBool
{
public: // ctors
    TriBool();
    TriBool(const bool is);

public: // const
    bool value() const;
    bool valid() const;
    bool cheap() const;
    bool invalid() const;
    bool isTrue() const;
    bool isFalse() const;
    bool isNull() const;
    operator bool () const;

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
inline bool TriBool::cheap() const { return ! value(); }
inline bool TriBool::invalid() const { return ! valid(); }
inline bool TriBool::isTrue() const { return value() && valid(); }
inline bool TriBool::isFalse() const { return cheap() && valid(); }
inline bool TriBool::isNull() const { return value() && invalid(); }
inline TriBool::operator bool() const { return isTrue(); }

