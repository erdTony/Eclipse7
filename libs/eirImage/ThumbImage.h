#pragma once
#include "eirImage.h"

#include "BaseImage.h"

#include <QtGlobal>
#include <QColor>

#include <Size.h>
#include <SCRect.h>

class EIRIMAGE_EXPORT ThumbImage : public BaseImage
{
public:
    ThumbImage();
    ThumbImage(const BaseImage &origImage,
               const Size thumbSize=Size(),
               const Qt::AspectRatioMode aspectMode=Qt::IgnoreAspectRatio,
               const bool aspectCenter=true,
               const QColor backColor=QColor());
    virtual ~ThumbImage() {;}

public: // const
    BaseImage origImage() const;
    Size thumbSize() const;
    Qt::AspectRatioMode aspectMode() const;
    bool aspectCenter() const;
    QColor backColor() const;
    SCRect origRect() const;

public: // static
    static void defaultSize(const Size sz);

private:
    void set();

private:
    const BaseImage cmOrigImage;
    const Size cmThumbSize;
    const Qt::AspectRatioMode cmAspectMode;
    const bool cmAspectCenter;
    const QColor cmBackColor;
    static Size smDefaultSize;
};
