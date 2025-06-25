#include "ThumbImage.h"

Size ThumbImage::smDefaultSize(192);

ThumbImage::ThumbImage()
    : cmAspectMode(Qt::KeepAspectRatio)
    , cmAspectCenter(false) {;}

ThumbImage::ThumbImage(const BaseImage &origImage,
                       const Size thumbSize,
                       const Qt::AspectRatioMode aspectMode,
                       const bool aspectCenter,
                       const QColor backColor)
    : cmOrigImage(origImage)
    , cmThumbSize(thumbSize)
    , cmAspectMode(aspectMode)
    , cmAspectCenter(aspectCenter)
    , cmBackColor(backColor)
{
    set();
}

void ThumbImage::defaultSize(const Size sz)
{
    smDefaultSize = sz;
}

void ThumbImage::set()
{

}
