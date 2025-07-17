#pragma once
#include "eirExe.h"

#include <QObject>

#include <QList>
#include <QRandomGenerator>
class QTimer;

#include <Queue.h>
#include <Types.h>

class EIREXE_EXPORT Random : public QObject
{
    Q_OBJECT
public: // types

public: // ctors
    explicit Random(QObject *parent = nullptr);

public slots:
    void initialize();
    void setup();
    void execute();
    void reseed(const DWORD dw);
    void dequeue();
    void dequeueF();
    void dequeue(const Count k);
    void dequeueF(const Count k);

signals: // public
    void initialized();
    void taken(const UINT &u);
    void takenF(const FLOAT &f);
    void dequeued(const UINT &u);
    void dequeuedF(const FLOAT &f);
    void directed(const UINT &u);
    void directedF(const FLOAT &f);

public: // const
    UINT take();
    UIntList take(const Count k, const UINT bound=0);
    FLOAT takeF();
    FloatList takeF(const Count k);
    UINT direct();
    UIntList direct(const Count k);
    FLOAT directF();
    FloatList directF(const Count k);

public: // non-const
    UIntList randomIota(const Count iotaCount);
    void randomize(UIntList &pList);

private: // const
    bool isFull() const;
    Count count() const;
    Count countF() const;

private slots:
    void clear();
    void pulse();
    void refill();
    void refillF();

signals: // private
    void pulsed();
    void refilled(const Count currentCount);
    void refilledF(const Count currentCount);

private:
    QRandomGenerator mGenerator;
    Queue<UINT> mUIntQueue;
    Queue<FLOAT> mFloatQueue;
    QTimer * mpPulseTimer=nullptr;

    // ================ properties ================
private:
    bool enableUInt=true;
    bool enableFloat=true;
    Milliseconds shortPulseMsec=100;
    Milliseconds longPulseMsec=1000;
    Count loCount=256;
    Count hiCount=2048;
    Count blockCount=512;
};


inline Count Random::count() const { return mUIntQueue.count(); }
inline Count Random::countF() const { return mFloatQueue.count(); }
