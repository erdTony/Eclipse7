#pragma once
#include "eirImage.h"

#include "BaseImage.h"

class EIRIMAGE_EXPORT GreyImage : public BaseImage
{
public:
    GreyImage();
    GreyImage(const BaseImage &other);

public: // virtual const
    virtual bool isPlanar() const;

};
