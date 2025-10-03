#include "ImageObject.h"

ImageObject::ImageObject(QObject *parent) : QObject{parent} {;}
ImageObject::ImageObject(const QImage img, QObject *parent)
    : QObject{parent} { set(img); }



QImage::Format ImageObject::qformat(const ImageType aType)
{
    QImage::Format result = QImage::Format_Invalid;
    switch (aType)
    {
    case ImageType::Grey:      result = QImage::Format_Grayscale8;     break;
    case ImageType::ARGB32:     result = QImage::Format_ARGB32;         break;
    case ImageType::LCDY:    case ImageType::LCDCr:   case ImageType::LCDCb:
    case ImageType::Red:    case ImageType::Green:    case ImageType::Blue:
    case ImageType::Index:     result = QImage::Format_Indexed8;       break;
    case ImageType::$null:     /* leave _Invalid */                    break;
    };
    return result;
}

// static
bool ImageObject::isPlanar(const ImageType aType)
{
    bool result = false;        // TODO switch
    if (aType == ImageType::Grey)          result = true;
    if (aType == ImageType::Index)         result = true;
    if (aType == ImageType::Red)        result = true;
    if (aType == ImageType::Green)        result = true;
    if (aType == ImageType::Blue)        result = true;
    if (aType == ImageType::LCDY)        result = true;
    if (aType == ImageType::LCDCr)       result = true;
    if (aType == ImageType::LCDCb)       result = true;
    return result;
}
