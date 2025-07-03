#include "BaseImage.h"

#include <SCRect.h>
#include <Size.h>

BaseImage::BaseImage() : mType(Image::$null) {;}
BaseImage::BaseImage(const Image::Type type, const BaseImage &other)
    : mType(type), mBaseImage(other.convertedTo(type).qImage()) {;}
BaseImage::BaseImage(const Image::Type aType, const QImage &qimage)
    : mType(aType), mBaseImage(qimage.convertedTo(Image::qformat(type()))) {;}
BaseImage::BaseImage(const Image::Type aType, const QPixmap &aPixmap)
    : mType(aType), mBaseImage(aPixmap.toImage().convertedTo(Image::qformat(type()))) {;}

Point BaseImage::center() const
{
    return qImage().rect().center();
}

Size BaseImage::size() const
{
    return qImage().size();
}

BaseImage BaseImage::convertedTo(const Image::Type type) const
{
    return BaseImage(type, qImage());
}

BaseImage BaseImage::scaledCrop(const QSize aCropSize,
    const unsigned int minScale, const unsigned int maxScale)
{
    BaseImage result;
    const Size cImageSize = size();
    const Size cNewSize(aCropSize, cImageSize.aspect());

    if (cImageSize == cNewSize) return it();             /*===\*/
    const qreal cScaleF = cImageSize.scaleToF(cNewSize);
    const unsigned cScale = qBound(minScale, unsigned(cScaleF), maxScale);
    if (cScale <= 1) return it();

    scale(cScale);
    return result = it();
}

void BaseImage::set(const BaseImage &rhs)
{
    mType = rhs.type();
    mBaseImage = rhs.qImage();
}

void BaseImage::set(const QImage &qi)
{
    mBaseImage = qi.convertedTo(Image::qformat(type()));
}

void BaseImage::scale(const signed int aRatio)
{
    Size tNewSize = size();
    if (aRatio < 0)
        tNewSize /= ( - aRatio);
    else if (aRatio > 0)
        tNewSize *= aRatio;
    qImage() = qImage().scaled(tNewSize);
}

QPixmap BaseImage::pixmap(const Size sz)
{
    QPixmap result;
    const Size cAdjustedSize = Size(sz, size());
    if (mSizePixmapMap.contains(cAdjustedSize))
    {
        result = mSizePixmapMap.value(cAdjustedSize);
    }
    else
    {
        result = QPixmap::fromImage(qImage()
            .scaledToHeight(cAdjustedSize.height()));
        mSizePixmapMap.insert(cAdjustedSize, result);
    }
    return result;
}

bool BaseImage::isPlanar() const
{
    return Image::isPlanar(mType);
}

