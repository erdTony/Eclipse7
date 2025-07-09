#pragma once
#include "eirImage.h"

#include <QObject>

#include <QImage>

class EIRIMAGE_EXPORT ImageObject : public QObject
{
    Q_OBJECT
public: // types
    enum Type
    {
        $null           = QImage::Format_Invalid,
        Grey            = QImage::Format_Grayscale8,
        Grey16          = QImage::Format_Grayscale16,
        Color           = QImage::Format_ARGB32,
        Index           = QImage::Format_Indexed8,
        $startNonQImage = 100,
        YPlane,
        CrPlane,
        CbPlane,
        $max
    };
    Q_ENUM(Type);

public:
    explicit ImageObject(QObject *parent = nullptr);

signals:

public:

public: // static
    static QImage::Format qformat(const ImageObject::Type aType);
    static bool isPlanar(const ImageObject::Type aType);

};
