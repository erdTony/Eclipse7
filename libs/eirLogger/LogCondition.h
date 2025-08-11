#pragma once
#include "eirLogger.h"

class QVariant;

class EIRLOGGER_EXPORT LogCondition
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
        NotLess,
        Greater,
        GreaterEqual,
        NotGreater,
        Positive,
        Zero,
        Negative,
        NonPos,
        NonZero,
        NonNeg,
    };

public: // ctors
    LogCondition();
    LogCondition(const Enum e);

public: // const
    bool isUnary() const;
    bool isBinary() const;
    operator int () const;
    bool evaluate(const QVariant &v);
    bool evaluate(const QVariant &v1, const QVariant &v2);

public: // non-const

public: // static
    bool isUnary(const Enum e);
    bool isBinary(const Enum e);

private:
    Enum mEnum=$null;
};

inline LogCondition::operator int() const { return int(mEnum); }
