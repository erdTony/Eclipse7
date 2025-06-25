#include "Grey16Image.h"

Grey16Image::Grey16Image() {}
Grey16Image::Grey16Image(const BaseImage &other) : BaseImage(other) {;}

bool Grey16Image::isPlanar() const
{
    return true;
}

