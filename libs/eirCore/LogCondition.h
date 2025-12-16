#pragma once
#include "eirCore.h"

class QVariant;

#include <AText.h>

class EIRCORE_EXPORT LogCondition
{
public: // types
    enum Enum
    {
        $null = 0,
        True,
        False,
        Equal,
        NotEqual,
        Less,
        LessEqual,
        NotGreater,
        Greater,
        GreaterEqual,
        NotLess,
        Positive,
        Zero,
        Negative,
        NonPos,
        NonZero,
        NonNeg,
        $max
    };

public: // ctors
    LogCondition();
    LogCondition(const Enum e);

public: // const
    bool isUnary() const;
    bool isBinary() const;
    bool isValid(const int i);
    bool evaluate(const QVariant &v);
    bool evaluate(const QVariant &v1, const QVariant &v2);
    int toInt() const;
    operator int () const;
    AText text() const;

public: // non-const
    void set(const int i);

public: // static
    bool isUnary(const Enum e);
    bool isBinary(const Enum e);

private:
    Enum mEnum=$null;
};

inline int LogCondition::toInt() const { return int(mEnum); }
inline LogCondition::operator int() const { return toInt(); }
