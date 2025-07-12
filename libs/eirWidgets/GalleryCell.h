#pragma once
#include "eirWidgets.h"

#include <QLabel>

#include <QImage>
#include <QPixmap>

#include <Ident.h>

#include "GalleryProperties.h"
class Gallery;

class EIRWIDGETS_EXPORT GalleryCell : public QLabel
{
    Q_OBJECT
public: // ctors
    explicit GalleryCell(Gallery *parent);
    explicit GalleryCell(const Ident &id, Gallery *parent);
    explicit GalleryCell(const Ident &id, const QImage &orig, Gallery *parent);

public slots:

signals:

public: // const
    bool isNull() const;

public: // non-const

public: // pointers
    Gallery * gallery() const;
    Gallery * gallery();
    GalleryProperties props() const;
    GalleryProperties &props();

private:
    Gallery * mpGallery=nullptr;
    Ident mIdent;
    QImage mOriginalImage;
    QImage mScaledImage;
    QPixmap mPixmap;
};

inline Gallery *GalleryCell::gallery() { Q_CHECK_PTR(mpGallery); return mpGallery; }
inline Gallery *GalleryCell::gallery() const { Q_CHECK_PTR(mpGallery); return mpGallery; }




