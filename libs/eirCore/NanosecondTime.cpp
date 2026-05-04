#include "NanosecondTime.h"

#include <chrono>

NanosecondTime::NanosecondTime(const Nanoseconds kTicks) { set(kTicks); }

bool NanosecondTime::isNull() const
{
    return -1 == mNanoTicks;
}

bool NanosecondTime::isValid() const
{
    return nanoYear(1580) <= mNanoTicks && mNanoTicks <= nanoYear(3000);
}

time_t NanosecondTime::timeT() const
{
    std::time_t result;
    std::chrono::time_point<std::chrono::system_clock,
                            std::chrono::duration<Nanoseconds> >
        tTPns( (std::chrono::duration<Nanoseconds>(mNanoTicks)) );
    result = std::chrono::system_clock::to_time_t(tTPns);
    return result;
}

SQWORD NanosecondTime::hecto() const
{
    return mNanoTicks / 100LL;
}

void NanosecondTime::set(const Nanoseconds kTicks)
{
    std::chrono::nanoseconds tKT(kTicks);
    if (0 == kTicks) // 0=use current
    {
        std::chrono::time_point tTPnow = std::chrono::system_clock::now();
        tKT = std::chrono::duration_cast<std::chrono::nanoseconds>(tTPnow.time_since_epoch());
    }
    mNanoTicks = tKT.count();
}

void NanosecondTime::hecto(const SQWORD hns)
{
    mNanoTicks = hns * 100LL;
}

// static
Nanoseconds NanosecondTime::nanoYear(const WORD year)
{
    return Nanoseconds(DWORDF(year) * 365.2422) * 24LL * 3600LL * nanoFactor();
}

std::time_t NanosecondTime::base()
{
    std::time_t result;
    std::chrono::time_point<std::chrono::system_clock,
                            std::chrono::duration<Nanoseconds> >
        tTPns( (std::chrono::duration<Nanoseconds>(0)) );
    result = std::chrono::system_clock::to_time_t(tTPns);
    return result;
}

Nanoseconds NanosecondTime::offset(const StructTM other)
{
    std::time_t tSTTbase = base();
    std::time_t tSTTother = other.timeT();
    return Nanoseconds(tSTTother) - Nanoseconds(tSTTbase);
}


