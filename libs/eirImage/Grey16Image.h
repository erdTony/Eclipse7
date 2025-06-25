#pragma once
#include "eirImage.h"

#include "BaseImage.h"

class EIRIMAGE_EXPORT Grey16Image : public BaseImage
{
public:
    Grey16Image();
    Grey16Image(const BaseImage &other);

public: // virtual const
    virtual bool isPlanar() const;

};
