#include "FrameImage.h"

FrameImage::FrameImage() {;}
FrameImage::FrameImage(const QImage &qimage) : BaseImage(ImageType::ARGB32, qimage) {;}
FrameImage::FrameImage(const BaseImage &other) : BaseImage(ImageType::ARGB32, other) {;}

bool FrameImage::isPlanar() const
{
    return false;
}
