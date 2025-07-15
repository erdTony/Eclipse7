#include "GalleryCell.h"

#include <QPainter>

#include "Gallery.h"

GalleryCell * GalleryCell::smpBlankCell=nullptr;

GalleryCell::GalleryCell(Gallery *parent) : QLabel{parent->widget()}, mpGallery(parent) {;}

bool GalleryCell::isNull() const
{
    if (mIdent.isNull()) return true;
    if (mOriginalImage.isNull()) return true;
    return false;
}


QImage GalleryCell::scaled()
{
    QImage result;
    SCRect tOrigRect(original().rect());
    if (props().modes() & Gallery::ImageAspect)
        tOrigRect.aspect(props().itemPixelSize().aspect());
    if (props().modes() & Gallery::ImageScale)
        result = original().scaled(tOrigRect.size());
    if (props().modes() & Gallery::ImageCrop)
        result = original().copy(tOrigRect);
    return result;
}

QPixmap GalleryCell::pixmap(const QImage &orig, const QColor border)
{
    QPixmap result(props().cellPixelSize());
    QPainter tPainter;
    Q_ASSERT(tPainter.begin(&result));
    tPainter.fillRect(SCRect(result.size()).toQRect(),
                 props().itemBackground());
    tPainter.fillRect(SCRect(result.size()).toQRect(),
                      props().itemBackground());
    SCRect tSrcRect(Size(orig.size()).min());
    SCRect tDstRect(props().itemPixelSize(),
                    props().cellPixelSize().center());
    tPainter.drawImage(tDstRect.toQRect(), orig, tSrcRect);
    if (border.isValid())
    {
        QPen tPen(QBrush(border), props().selectionWidth());
        tPainter.setPen(tPen);
        tPainter.drawRect((SCRect(props().itemPixelSize())
                         + props().selectionWidth() / 2).toQRect());
    }
    tPainter.end();
    return result;
}

GalleryCell *GalleryCell::blankCell()
{
    GalleryCell * result = smpBlankCell;
    if (smpBlankCell == nullptr)
    {
        QImage tImage(gallery()->props().itemPixelSize(),
                      QImage::Format_ARGB32);
        tImage.fill(gallery()->props().itemForeground());
        QPixmap tPixmap = pixmap(tImage);
        if ( ! tImage.isNull() && ! tPixmap.isNull())
        {
            result = new GalleryCell(gallery());
            result->mOriginalImage = result->mScaledImage = tImage;
            result->mPixmap = tPixmap;
            smpBlankCell = result;
        }
    }
    return result;
}

GalleryProperties GalleryCell::props() const { return gallery()->props(); }
GalleryProperties &GalleryCell::props() { return gallery()->props(); }
