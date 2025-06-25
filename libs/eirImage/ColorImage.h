#pragma once
#include "eirImage.h"

#include "BaseImage.h"

class EIRIMAGE_EXPORT ColorImage : public BaseImage
{
public: // ctors
    ColorImage();
    virtual ~ColorImage() {;}
    ColorImage(const BaseImage &other);

public: // virtual const
    virtual bool isPlanar() const;

};
