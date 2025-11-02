#pragma once
#include "eirImage.h"

#include <QMap>
#include <QImage>
#include <QPixmap>

#include <Point.h>
#include <Size.h>

#include "ImageType.h"

class EIRIMAGE_EXPORT BaseImage
{
public: // ctors
    BaseImage(); // TODO
    BaseImage(const ImageType type, const BaseImage &other);
    BaseImage(const ImageType::Value type, const QImage &qimage);
    BaseImage(const ImageType::Value type, const QPixmap &aPixmap);

public: // const
    QImage qImage() const;
    Point center() const;
    Size size() const;
    BaseImage convertedTo(const ImageType type) const;
    BaseImage scaledCrop(const QSize aCropSize,
        const unsigned minScale=4, const unsigned maxScale=4);

public: // non-const
    void set(const BaseImage &rhs);
    void set(const QImage &qi);
    void scale(const signed aRatio);
    QPixmap pixmap(const Size sz);

public: // virtual const
    virtual ImageType type() const;
    virtual bool isPlanar() const;

public: // pointer
    QImage & qImage();
    BaseImage it() const;
    BaseImage & it();

private:
    ImageType mType=ImageType::$null;
    QImage mBaseImage;
    QMap<Size, QPixmap> mSizePixmapMap;
};

inline QImage BaseImage::qImage() const { return mBaseImage; }
inline QImage & BaseImage::qImage() { return mBaseImage; }
inline ImageType BaseImage::type() const { return mType; }
inline BaseImage BaseImage::it() const { return *this; }
inline BaseImage &BaseImage::it() { return *this; }
