#pragma once
#include "eirImage.h"

class EIRIMAGE_EXPORT ImageEncoding
{
public: // types
    enum Value
    {
        $null = 0,
        RawPixel,
        RawPlanes,
        JpegBytes,
        PngBytes,
        BmpBytes,
        YCrCb444,
        YCrCb422,
        YCrCb420,
        YCrCb411,
    };

public: // ctors
    ImageEncoding();
    ImageEncoding(const Value v);

public: // const
    bool isNull() const;
    enum Value value() const;
    operator int () const;
    operator Value () const;

public: // non-const
    void set(const enum Value v);

private:
    enum Value   mValue=$null;

};

inline bool ImageEncoding::isNull() const { return $null == mValue; }
inline ImageEncoding::Value ImageEncoding::value() const { return mValue; }
inline ImageEncoding::operator int() const {return (int)value(); }
inline ImageEncoding::operator Value() const { return value(); }
