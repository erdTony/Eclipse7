#pragma once

#include "StructTM.h"
#include "Types.h"

class NanosecondTime
{
public: // types

public: // ctors
    NanosecondTime(const Nanoseconds kTicks=0); // 0=use current
    NanosecondTime(const std::time_t kSTT);

public: // const
    Nanoseconds value() const;
    bool isNull() const;
    bool isValid() const;
    std::time_t timeT() const;
    SQWORD hecto() const;

public: // non-const
    void set(const Nanoseconds kTicks);  // 0=use current
    void set(const std::time_t kSTT);
    void hecto(const SQWORD hns);
    void nullify();

public: // static
    static Nanoseconds nanoFactor();
    static Nanoseconds nanoYear(const WORD year);
    static std::time_t base();
    static Nanoseconds offset(const StructTM other);

private:
    Nanoseconds mNanoTicks=-1;
};

inline Nanoseconds NanosecondTime::value() const { return mNanoTicks; }
inline void NanosecondTime::nullify() { mNanoTicks = -1; }
inline Nanoseconds NanosecondTime::nanoFactor() { return 1000000000LL; }
