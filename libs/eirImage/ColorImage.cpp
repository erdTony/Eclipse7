#include "ColorImage.h"

#include <Point.h>
#include <SCRect.h>

ColorImage::ColorImage() {;}
ColorImage::ColorImage(const QImage &qimage) : BaseImage(ImageType::ARGB32, qimage) {;}
ColorImage::ColorImage(const BaseImage &other) : BaseImage(ImageType::ARGB32, other) {;}

bool ColorImage::isPlanar() const
{
    return false;
}

SCRect ColorImage::rect() const
{
    return qImage().rect();
}

QRgb ColorImage::pixel(const Point pt) const
{
    return qImage().pixel(pt);
}

void ColorImage::pixel(const Point pt, const QRgb rgb)
{
    qImage().setPixel(pt, rgb);
}
