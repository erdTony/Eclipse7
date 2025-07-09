#pragma once
#include "eirImage.h"

#include <QMap>
#include <QImage>
#include <QPixmap>

#include <Point.h>
#include <Size.h>

#include "ImageObject.h"

class EIRIMAGE_EXPORT BaseImage
{
public: // ctors
    BaseImage();
    BaseImage(const ImageObject::Type type, const BaseImage &other);
    BaseImage(const ImageObject::Type aType, const QImage &qimage);
    BaseImage(const ImageObject::Type aType, const QPixmap &aPixmap);

public: // const
    QImage qImage() const;
    Point center() const;
    Size size() const;
    BaseImage convertedTo(const ImageObject::Type type) const;
    BaseImage scaledCrop(const QSize aCropSize,
        const unsigned minScale=4, const unsigned maxScale=4);

public: // non-const
    void set(const BaseImage &rhs);
    void set(const QImage &qi);
    QImage & qImage();
    void scale(const signed aRatio);
    QPixmap pixmap(const Size sz);

public: // virtual const
    virtual ImageObject::Type type() const;
    virtual bool isPlanar() const;

private: // pointer
    BaseImage it() const;
    BaseImage & it();

private:
    ImageObject::Type mType=ImageObject::$null;
    QImage mBaseImage;
    QMap<Size, QPixmap> mSizePixmapMap;
};

inline QImage BaseImage::qImage() const { return mBaseImage; }
inline QImage & BaseImage::qImage() { return mBaseImage; }
inline ImageObject::Type BaseImage::type() const { return mType; }
inline BaseImage BaseImage::it() const { return *this; }
inline BaseImage &BaseImage::it() { return *this; }
