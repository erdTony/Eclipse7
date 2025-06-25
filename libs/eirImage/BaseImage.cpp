#include "BaseImage.h"

#include <SCRect.h>
#include <Size.h>

BaseImage::BaseImage() : mType(Image::$null) {;}
BaseImage::BaseImage(const Image::Type aType, const QImage &aQImage)
    : mType(aType)
    , mBaseImage(aQImage.convertedTo(Image::qformat(type()))) {;}
BaseImage::BaseImage(const Image::Type aType, const QPixmap &aPixmap)
    : mType(aType)
    , mBaseImage(aPixmap.toImage().convertedTo(Image::qformat(type()))) {;}

QPoint BaseImage::center() const
{
    return baseImage().rect().center();
}

QSize BaseImage::size() const
{
    return baseImage().size();
}

BaseImage BaseImage::scaledCrop(const QSize aCropSize,
    const unsigned int minScale, const unsigned int maxScale)
{
    BaseImage result;
    const Size cImageSize = size();
    const Size cNewSize(aCropSize, cImageSize.aspect());

    if (cImageSize == cNewSize) return it();             /*===\*/
    const qreal cScaleF = cImageSize.scaleF(cNewSize);
    const unsigned cScale = qBound(minScale, unsigned(cScaleF), maxScale);
    if (cScale <= 1) return it();

    scale(cScale);
    return result = it();
}

void BaseImage::set(const BaseImage &rhs)
{
    mType = rhs.type();
    mBaseImage = rhs.baseImage();
}

void BaseImage::set(const QImage &aQImage)
{
    mBaseImage = aQImage.convertedTo(Image::qformat(type()));
}

void BaseImage::scale(const signed int aRatio)
{
    Size tNewSize = size();
    if (aRatio < 0)
        tNewSize /= ( - aRatio);
    else if (aRatio > 0)
        tNewSize *= aRatio;
    baseImage() = baseImage().scaled(tNewSize);
}

bool BaseImage::isPlanar() const
{
    return Image::isPlanar(mType);
}

