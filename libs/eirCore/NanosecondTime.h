#pragma once

#include "Types.h"

class NanosecondTime
{
public: // types
    const static NanoSeconds cmNanoFactor = 1000000000LL;

public: // ctors
    NanosecondTime(const NanoSeconds kTicks=0); // 0=use current

public: // const
    bool isNull() const;
    bool isValid() const;
    std::time_t timeT() const;
    SQWORD hecto() const;
    QWORD hectoGregorian() const;

public: // non-const
    void set(const NanoSeconds kTicks=0);  // 0=use current
    void hecto(const SQWORD hns);
    void hectoGregorian(const QWORD hgns);
    void nullify();

public: // static
    static NanoSeconds nanoYear(const WORD year);

private:
    NanoSeconds mNanoTicks=-1;
};

inline void NanosecondTime::nullify() { mNanoTicks = -1; }
