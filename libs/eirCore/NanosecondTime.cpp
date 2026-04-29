#include "NanosecondTime.h"

#include <chrono>

NanosecondTime::NanosecondTime(const NanoSeconds kTicks) { set(kTicks); }

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
                            std::chrono::duration<NanoSeconds> >
        tTPns( (std::chrono::duration<NanoSeconds>(mNanoTicks)) );
    result = std::chrono::system_clock::to_time_t(tTPns);
    return result;
}

SQWORD NanosecondTime::hecto() const
{
    return mNanoTicks / 100LL;
}

void NanosecondTime::set(const NanoSeconds kTicks)
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
NanoSeconds NanosecondTime::nanoYear(const WORD year)
{
    return NanoSeconds(DWORDF(year) * 365.2422) * 24LL * 3600LL * cmNanoFactor;
}


