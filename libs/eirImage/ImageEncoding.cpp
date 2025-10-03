#include "ImageEncoding.h"

ImageEncoding::ImageEncoding() : mValue($null) {;}
ImageEncoding::ImageEncoding(const Value v) : mValue(v) {;}

void ImageEncoding::set(const Value v)
{
    mValue = v;
}



