#pragma once
#include "eirWidgets.h"

#include <QLabel>

#include <QImage>
#include <QPixmap>

#include <Id.h>
#include <SCRect.h>
class Uid;

#include "GalleryProperties.h"
class Gallery;

class EIRWIDGETS_EXPORT GalleryCell : public QLabel
{
    Q_OBJECT
public: // ctors
    GalleryCell(const bool blank=true, Gallery *parent=nullptr);
    GalleryCell(const Id &id, Gallery *parent);
    GalleryCell(const Id &id, const QImage &orig, Gallery *parent);

public slots:

signals:

public: // const
    bool isBlank() const;
    bool isNull() const;
    Uid uid() const;
    Id id() const;
    SCRect rect() const;
    QImage original() const;

public: // non-const
    QImage scaled();
    QPixmap generate(const QImage &orig, const QColor border=QColor());
    void setBlank();

public: // pointers
    Gallery * gallery() const;
    Gallery * gallery();
    GalleryProperties props() const;
    GalleryProperties &props();

private:
    Gallery * mpGallery=nullptr;
    bool mBlank=false;
    Id mIdent;
    QImage mOriginalImage;
    QImage mScaledImage;
    QPixmap mPixmap;
};

inline Gallery *GalleryCell::gallery() { Q_CHECK_PTR(mpGallery); return mpGallery; }
inline bool GalleryCell::isBlank() const { return mBlank; }

inline Id GalleryCell::id() const { return mIdent; }
inline SCRect GalleryCell::rect() const { return SCRect(props().cellPixelSize()); }
inline QImage GalleryCell::original() const { return mOriginalImage; }
inline Gallery *GalleryCell::gallery() const { Q_CHECK_PTR(mpGallery); return mpGallery; }




