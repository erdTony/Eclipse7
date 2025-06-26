#pragma once
#include "eirImage.h"

#include "BaseImage.h"
class Point;
class SCRect;

class EIRIMAGE_EXPORT ColorImage : public BaseImage
{
public: // ctors
    ColorImage();
    ColorImage(const QImage &qimage);
    ColorImage(const BaseImage &other);
    virtual ~ColorImage() {;}

public: // virtual const
    virtual bool isPlanar() const;

public: // const
    SCRect rect() const;
    QRgb pixel(const Point pt) const;

public: // non-const
    void pixel(const Point pt, const QRgb rgb);

};
