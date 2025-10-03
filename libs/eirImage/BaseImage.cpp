#include "BaseImage.h"

#include <SCRect.h>
#include <Size.h>

BaseImage::BaseImage() : mType(ImageType::$null) {;}
BaseImage::BaseImage(const ImageType type, const BaseImage &other)
    : mType(type), mBaseImage(other.convertedTo(type()).qImage()) {;}
BaseImage::BaseImage(const ImageType::Value type, const QImage &qimage)
    : mType(type), mBaseImage(qimage.convertedTo(ImageType::qformat(type))) {;}
BaseImage::BaseImage(const ImageType::Value type, const QPixmap &aPixmap)
    : mType(type), mBaseImage(aPixmap.toImage().convertedTo(ImageType::qformat(type))) {;}

Point BaseImage::center() const
{
    return qImage().rect().center();
}

Size BaseImage::size() const
{
    return qImage().size();
}

BaseImage BaseImage::convertedTo(const ImageType type) const
{
    return BaseImage(type.value(), qImage());
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
    mBaseImage = qi.convertedTo(ImageType::qformat(mType.value()));
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
    const Size cAdjustedSize(sz, size().aspect());
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
    return ImageType::isPlanar(mType());
}

