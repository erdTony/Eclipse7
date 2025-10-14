#pragma once
#include "eirImage.h"

#include "BaseImage.h"

class EIRIMAGE_EXPORT FrameImage : public BaseImage
{   // TODO Move to eirObjDet
public:

public: // ctors
    FrameImage();
    FrameImage(const QImage &qimage);
    FrameImage(const BaseImage &other);
    virtual ~FrameImage() {;}

public: // virtual const
    virtual bool isPlanar() const;

private:
    // TODO: cvMat grey
    // TODO: ObjDetResultList

};
