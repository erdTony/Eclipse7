#include "ImageType.h"

ImageType::ImageType() : mValue($null) {;}
ImageType::ImageType(const enum Value v) : mValue(v) {;}

int ImageType::byteDepth() const
{
    return (int)(mValue) / 1000;
}

bool ImageType::isPlanar() const
{
    return 1 == byteDepth();
}

// ---- static ----------------------------

QImage::Format ImageType::qformat(const Value v)
{
    QImage::Format result = QImage::Format_Invalid;
    switch (v)
    {
    case RGB24:                 result = QImage::Format_RGB888;     break;
    case ARGB32:                result = QImage::Format_ARGB32;     break;
    case Black:     case Valu:      case Level:
    case LCDY:      case LCAY:  result = QImage::Format_Grayscale8; break;
    case $null:                 /* leave invalid */                 break;
    default:                    result = QImage::Format_Indexed8;   break;
    }
    return result;
}

int ImageType::byteDepth(const enum Value v)
{
    return ImageType(v).byteDepth();
}

bool ImageType::isPlanar(const enum Value v)
{
    return ImageType(v).isPlanar();
}

