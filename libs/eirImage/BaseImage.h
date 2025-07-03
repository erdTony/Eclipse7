#pragma once
#include "eirImage.h"

#include <QMap>
#include <QImage>
#include <QPixmap>

#include <Point.h>
#include <Size.h>

#include "Image.h"

class EIRIMAGE_EXPORT BaseImage
{
public: // ctors
    BaseImage();
    BaseImage(const Image::Type type, const BaseImage &other);
    BaseImage(const Image::Type aType, const QImage &qimage);
    BaseImage(const Image::Type aType, const QPixmap &aPixmap);

public: // const
    QImage qImage() const;
    Point center() const;
    Size size() const;
    BaseImage convertedTo(const Image::Type type) const;
    BaseImage scaledCrop(const QSize aCropSize,
        const unsigned minScale=4, const unsigned maxScale=4);

public: // non-const
    void set(const BaseImage &rhs);
    void set(const QImage &qi);
    QImage & qImage();
    void scale(const signed aRatio);
    QPixmap pixmap(const Size sz);

public: // virtual const
    virtual Image::Type type() const;
    virtual bool isPlanar() const;

private: // pointer
    BaseImage it() const;
    BaseImage & it();

private:
    Image::Type mType=Image::$null;
    QImage mBaseImage;
    QMap<Size, QPixmap> mSizePixmapMap;
};

inline QImage BaseImage::qImage() const { return mBaseImage; }
inline QImage & BaseImage::qImage() { return mBaseImage; }
inline Image::Type BaseImage::type() const { return mType; }
inline BaseImage BaseImage::it() const { return *this; }
inline BaseImage &BaseImage::it() { return *this; }
