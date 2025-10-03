#pragma once
#include "eirImage.h"

#include <QImage>

class EIRIMAGE_EXPORT ImageType
{
public: // types
    enum Value
    {
        $null       = 0,
        Index       = 1001,
        Opacity, // AKA Alpha
        Red, Green, Blue, Grey,
        Cyan, Magenta, Yellow, Black,
        Hue, Saturation, Valu, Level,
        LCDY, LCDCr, LCDCb,
        LCAY, LCAU, LCAV,
        RGB24       = 3051,
        HSV24,
        HSL24,
        YCC24,
        YUV24,
        ARGB32      = 4101,
        CMYK32,
        AYCC32,
        AYUV32,
    };
    typedef QList<Value> List;

public: // ctors
    ImageType();
    ImageType(const enum Value v);

public: // const
    bool isNull() const;
    enum Value value() const;
    int byteDepth() const;
    bool isPlanar() const;
    operator int () const;
    enum Value operator () () const;

public: // non-const
    void set(const enum Value v);

public: // static
    static QImage::Format qformat(const enum Value v);
    static int byteDepth(const enum Value v);
    static bool isPlanar(const enum Value v);

private:
    enum Value   mValue=$null;
};

inline bool ImageType::isNull() const { return $null == mValue; }
inline ImageType::operator int() const { return value(); }
inline ImageType::Value ImageType::operator ()() const { return value(); }
inline enum ImageType::Value ImageType::value() const { return mValue; }
inline void ImageType::set(const enum Value v) { mValue = v; }
