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
    mpPulseTimer->start(shortPulseMsec);
    emit initialized();
}

void Random::setup()
{

}

void Random::execute()
{

}

void Random::reseed(const DWORD dw)
{
    clear();
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
    UINT result = mUIntQueue.dequeue();
    emit taken(result);
    return result;
}

UIntList Random::take(const Count k, const UINT bound)
{
    UIntList result;
    if (k <= count())
    {
        while (result.count() < k)
            result.append(take());
    }
    else
    {
        result = direct(k);
    }
    if (bound)
        for (Index ix = 0; ix < k; ++ix)
            result[ix] %= bound;
    return result;
}

FLOAT Random::takeF()
{
    UINT result = mUIntQueue.dequeue();
    emit taken(result);
    return result;
}

FloatList Random::takeF(const Count k)
{
    FloatList result;
    if (k <= count())
    {
        while (result.count() < k)
            result.append(takeF());
    }
    else
    {
        result = directF(k);
    }
    return result;
}

UINT Random::direct()
{
    UINT result = mGenerator.generate64();
    emit directed(result);
    return result;
}

UIntList Random::direct(const Count k)
{
    UIntList result;
    while (result.count() < k)
        result.append(direct());
    return result;
}

FLOAT Random::directF()
{
    FLOAT result = mGenerator.generateDouble();
    emit directedF(result);
    return result;
}

FloatList Random::directF(const Count k)
{
    FloatList result;
    while (result.count() < k)
        result.append(directF());
    return result;
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

void Random::pulse()
{
    Q_CHECK_PTR(mpPulseTimer);
    mpPulseTimer->setInterval(isFull() ? longPulseMsec : shortPulseMsec);
    emit pulsed();
}

void Random::refill()
{
    UIntList tList;
    while (tList.count() < blockCount)
        tList.append(mGenerator.generate64());
    mUIntQueue.enqueue(tList);
    emit refilled(mUIntQueue.count());
}

void Random::refillF()
{
    FloatList tList;
    while (tList.count() < blockCount)
        tList.append(mGenerator.generateDouble());
    mFloatQueue.enqueue(tList);
    emit refilledF(mFloatQueue.count());
}
