#pragma once
#include "eirWidgets.h"

#include <QLabel>

#include <QImage>
#include <QPixmap>

#include <Ident.h>
#include <SCRect.h>
class Uid;

#include "GalleryProperties.h"
class Gallery;

class EIRWIDGETS_EXPORT GalleryCell : public QLabel
{
    Q_OBJECT
public: // ctors
    GalleryCell(Gallery *parent);
    GalleryCell(const Ident &id, Gallery *parent);
    GalleryCell(const Ident &id, const QImage &orig, Gallery *parent);

public slots:

signals:

public: // const
    bool isNull() const;
    Uid uid() const;
    Ident ident() const;
    SCRect rect() const;

public: // non-const
    QImage original();
    QImage scaled();
    QPixmap pixmap(const QImage &orig, const QColor border=QColor());
    GalleryCell * blankCell();

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
    static GalleryCell * smpBlankCell;
};

inline Gallery *GalleryCell::gallery() { Q_CHECK_PTR(mpGallery); return mpGallery; }
inline Uid GalleryCell::uid() const { return ident().uid(); }
inline Ident GalleryCell::ident() const { return mIdent; }
inline SCRect GalleryCell::rect() const { return SCRect(props().cellPixelSize()); }
inline QImage GalleryCell::original() { return mOriginalImage; }
inline Gallery *GalleryCell::gallery() const { Q_CHECK_PTR(mpGallery); return mpGallery; }




