#pragma once
#include "eirImage.h"

class EIRIMAGE_EXPORT ImageClass
{
public: // types
    enum Value
    {
        $null           = 0,
        Frame           = 1001,
        SeqFrame,
        DetectedFace    = 2001,
        NormalFace      = 3001,
        ReconFace,
        BodyCrop        = 4001,
        Height,
    };

public: // ctors
    ImageClass();
    ImageClass(const enum Value v);

public: // const
    bool isNull() const;
    enum Value value() const;
    operator int () const;
    operator enum Value () const;

public: // non-const
    void set(const enum Value v);

private:
    enum Value   mValue=$null;

};

inline bool ImageClass::isNull() const { return $null == mValue; }
inline ImageClass::Value ImageClass::value() const { return mValue; }
inline ImageClass::operator int() const {return (int)value(); }
inline ImageClass::operator Value() const { return value(); }
