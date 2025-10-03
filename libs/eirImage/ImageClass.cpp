#include "ImageClass.h"

ImageClass::ImageClass() : mValue($null) {;}
ImageClass::ImageClass(const Value v) : mValue(v) {;}

void ImageClass::set(const Value v)
{
    mValue = v;
}

