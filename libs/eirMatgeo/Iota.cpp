#include "Iota.h"

void Iota::set()
{
    clear();
}

void Iota::set(const Count k)
{
    clear();
    reserve(k);
    Index tIx = 0;
    while (Count(count()) < k)
        append(tIx++);
}

void Iota::set(const Count k, const unsigned int org)
{
    clear();
    reserve(k);
    Index tIx = org;
    while (Count(count()) < k)
        append(tIx++);
}

void Iota::set(const Count k, const unsigned int org, const unsigned int delta)
{
    clear();
    reserve(k);
    Index tIx = org;
    while (Count(count()) < k)
    {
        append(tIx);
        tIx += delta;
    }
}
