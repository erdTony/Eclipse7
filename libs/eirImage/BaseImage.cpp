#include "BaseImage.h"

#include <SCRect.h>
#include <Size.h>

BaseImage::BaseImage() : mType(ImageObject::$null) {;}
BaseImage::BaseImage(const ImageObject::Type type, const BaseImage &other)
    : mType(type), mBaseImage(other.convertedTo(type).qImage()) {;}
BaseImage::BaseImage(const ImageObject::Type aType, const QImage &qimage)
    : mType(aType), mBaseImage(qimage.convertedTo(ImageObject::qformat(type()))) {;}
BaseImage::BaseImage(const ImageObject::Type aType, const QPixmap &aPixmap)
    : mType(aType), mBaseImage(aPixmap.toImage().convertedTo(ImageObject::qformat(type()))) {;}

Point BaseImage::center() const
{
    return qImage().rect().center();
}

Size BaseImage::size() const
{
    return qImage().size();
}

BaseImage BaseImage::convertedTo(const ImageObject::Type type) const
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
    mBaseImage = qi.convertedTo(ImageObject::qformat(type()));
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
    return ImageObject::isPlanar(mType);
}

