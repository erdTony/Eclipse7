#pragma once

#include <QObject>

#include <QRandomGenerator64>

#include "Types.h"

class RandomGenerator : public QObject
{
    Q_OBJECT
public:

public:
    explicit RandomGenerator(QObject *parent = nullptr);
    RandomGenerator(const DWORD seed, QObject *parent = nullptr);

public slots:
    void initialize(const DWORD seed);
    void loadInteger(const Count min=0);
    void loadFloat(const Count min=0);
    void loadIntegers();
    void loadFloats();
    void checkCounts();

signals:
    void initialized();
    void loadedInteger(const Count k);
    void loadedFloat(const Count k);
    void taken(const QWORD qw, const Count k);
    void taken(const FLOAT dwf, const Count k);
    void taken(const QWordList qws, const Count k);
    void taken(const FloatList dfs, const Count k);

public: // const
    Count integerCount() const;
    Count floatCount() const;
    bool isIntegerEmpty() const;
    bool isFloatEmpty() const;

public: // non-const
    BYTE byte();
    WORD word();
    DWORD dword();
    QWORD qword();
    OWORD oword();
    WORDF wordF();
    FLOAT dwordF();
    QWordList qwords(const Count k);
    FloatList qwordsF(const Count k);

private:
    QWORD take();
    FLOAT takeF();

private:
    QWordList mIntegerList;
    FloatList mFloatList;

    // ---------------- properties ----------------
    Count mLoadCount = 256;
    Count mLowCount = 64;
};

inline Count RandomGenerator::integerCount() const { return mIntegerList.count(); };
inline Count RandomGenerator::floatCount() const { return mFloatList.count(); };
inline bool RandomGenerator::isIntegerEmpty() const { return 0 == mIntegerList.count(); };
inline bool RandomGenerator::isFloatEmpty() const { return 0 == mFloatList.count(); };
