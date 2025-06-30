#include "Random.h"

#include <QTimer>

#include <Iota.h>

Random::Random(QObject *parent)
    : QObject{parent}
    , mGenerator(QRandomGenerator::securelySeeded())
    , mpPulseTimer(new QTimer(this))
{
    setObjectName("Random");
    Q_CHECK_PTR(mpPulseTimer);
    mpPulseTimer->setObjectName("Random:PulseTimer");
}

void Random::initialize()
{
    Q_CHECK_PTR(mpPulseTimer);
    Q_ASSERT(connect(mpPulseTimer, &QTimer::timeout,
                     this, &Random::pulse));
    if (enableUInt)
        Q_ASSERT(connect(this, &Random::pulsed,
                         this, &Random::refill));
    if (enableFloat)
        Q_ASSERT(connect(this, &Random::pulsed,
                         this, &Random::refillF));
    // TODO

    emit initialized();
}

void Random::reseed(const DWORD dw)
{
    mGenerator.seed(dw);
}

void Random::dequeue()
{

}

void Random::dequeueF()
{

}

void Random::dequeue(const Count k)
{

}

void Random::dequeueF(const Count k)
{

}

UINT Random::take()
{

}

UIntList Random::take(const Count k, const UINT bound)
{
    UIntList result = (k >= count()) ? mUIntQueue.dequeue(k) : direct(k);
    if (bound)
        for (Index ix = 0; ix < k; ++ix)
            result[ix] %= bound;
    return result;
}

FLOAT Random::takeF()
{

}

FloatList Random::takeF(const Count k)
{

}

UINT Random::direct()
{

}

UIntList Random::direct(const Count k)
{

}

FLOAT Random::directF()
{

}

FloatList Random::directF(const Count k)
{

}

UIntList Random::randomIota(const Count iotaCount)
{
    UIntList result = Iota(iotaCount);
    randomize(result);
    return result;
}

void Random::randomize(UIntList &pList)
{
    const Count cCount = pList.count();
    UIntList ixSwapList = take(cCount);
    for (Index ix = 0; ix < Index(cCount); ++ix)
        qSwap(pList[ix], pList[ixSwapList[ix]]);
}



void Random::pulse()
{
    Q_CHECK_PTR(mpPulseTimer);
    mpPulseTimer->setInterval(isFull() ? longPulseMsec : shortPulseMsec);
    emit pulsed();
}

void Random::refill()
{

}

void Random::refillF()
{

}

bool Random::isFull() const
{
    return (enableUInt && count() >= hiCount)
           && (enableFloat && countF() >= hiCount);
}

void Random::clear()
{
    mUIntQueue.clear();
    mFloatQueue.clear();
}
