#include "Binary.h"

Binary::Round Binary::smRound = Binary::$null;

Binary::Binary() : mPower(0), mValue(1) {;}
Binary::Binary(const Value val, const Round r) { set(val, r); }

void Binary::set(const Value val, Round r)
{
    if ($null == r) r = round();
    value(val);
    Value tDiff = val - mValue;
    switch (($null == r) ? round() : r)
    {
    case $null:
    case down:      /* value() makes it down */             break;
    case up:        if (tDiff > 0)          preincrement(); break;
    case closest:   if (tDiff > mValue / 2) preincrement(); break;
    }
}

void Binary::power(const BYTE pow)
{
    mPower = pow, mValue = 1LL << pow;
}

void Binary::value(Value val)
{
    mPower = 0;
    do
    {
        ++mPower;
    } while (val >>= 1);
    mValue = 1LL << mPower;
}

Binary Binary::predecrement()
{
    if (power() > 0) power(power() - 1);
    return it();
}

Binary Binary::preincrement()
{
    if (power() < 255) power(power() + 1);
    return it();
}




