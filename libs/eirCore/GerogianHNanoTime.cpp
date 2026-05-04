#include "GerogianHNanoTime.h"

#include "NanosecondTime.h"
#include "RandomGenerator.h"

GerogianHNanoTime::GerogianHNanoTime()
{
    mLastMacAddress = NetworkMacAddress(false);
    mLastSequence = 0;
    mLastHNanoTick = 0;
}

SQWORD GerogianHNanoTime::generate(const SQWORD timeStampSec)
{
    SQWORD result = (timeStampSec * NanosecondTime::nanoFactor() / 100LL)
            - gregorianOffsetHNanoSec();
    const NetworkMacAddress cMacAddress(true);
    if (cMacAddress != mLastMacAddress || result < mLastHNanoTick)
    {
        RandomGenerator tRandom; // TODO Singleton, no singleShot's
        mCurrentSequence = tRandom.word();
    }
    else
    {
        mCurrentSequence = mLastSequence + 1;
    }
    mCurrentHNanoTick = result;
    mCurrentMacAddress = cMacAddress;
    mLastSequence = mCurrentSequence;
    mLastHNanoTick = mCurrentHNanoTick;
    mLastMacAddress = mCurrentMacAddress;
    return result;
}

SQWORD GerogianHNanoTime::gregorianOffsetHNanoSec()
{
    static SQWORD result = 0;
    if (0 == result)
    {
        struct tm tSTMGreg = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        tSTMGreg.tm_year = 1900 - 1582,
            tSTMGreg.tm_mon = 10,
            tSTMGreg.tm_mday = 15;
        std::time_t tSecGreg = std::mktime(&tSTMGreg);
        result = tSecGreg * NanosecondTime::nanoFactor() / 100LL;
    }
    return result;
}

SQWORD GerogianHNanoTime::currentHNanoSec()
{
    SQWORD result = NanosecondTime::nanoFactor() / 100LL;
    const std::chrono::time_point<std::chrono::system_clock> cSCTPNow
        = std::chrono::system_clock::now();
    const std::time_t cSecNow = std::chrono::system_clock::to_time_t(cSCTPNow);
    result *= cSecNow;
    return result;
}


