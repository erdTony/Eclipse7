#pragma once
#include "eirImage.h"

#include <QObject>

#include <QImage>
#include <QList>
#include <QMap>
#include <QPair>

#include <Rational.h>
#include <Size.h>

#include "ImageType.h"
#include "BaseImage.h"

class EIRIMAGE_EXPORT ImageObject : public QObject
{
    Q_OBJECT
public: // types
    typedef QPair<ImageType, Size> TypeSize;
    typedef QList<ImageType> TypeList;
    typedef QMap<TypeSize, BaseImage> TypeSizeImageMap;

public:
    explicit ImageObject(QObject *parent = nullptr);
    explicit ImageObject(const QImage img,
                         QObject *parent = nullptr);
    void ctor();

public slots:
    void set(const QImage &img) { /* TODO */ ; }
    void set(const QImage &img, const Size resize) { /* TODO */ ; }
    void set(const QImage &img, const Rational resizeR) { /* TODO */ ; }
    void generate(const Size sz) { /* TODO */ ; }
    void generate(const Size::List szs) { /* TODO */ ; }
    void generate(const ImageType type) { /* TODO */ ; }
    void generate(const ImageType::List types) { /* TODO */ ; }

signals:

public:

private:
    Size mInputSize;
    TypeSizeImageMap mTypeSizeImageMap;

public: // static
    static QImage::Format qformat(const ImageType aType);
    static bool isPlanar(const ImageType aType);

};
