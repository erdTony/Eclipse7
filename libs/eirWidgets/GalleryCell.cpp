#include "GalleryCell.h"

#include <QPainter>

#include "Gallery.h"


GalleryCell::GalleryCell(const bool blank, Gallery *parent)
    : QLabel{parent->widget()}
    , mpGallery(parent)
    , mBlank(blank)
{
    setObjectName(QString("GalleryCell:%1")
                      .arg(isBlank() ? "Blank" : "null"));
}

GalleryCell::GalleryCell(const Id &id, Gallery *parent)
    : QLabel{parent->widget()}
    , mpGallery(parent)
    , mBlank(false)
    , mIdent(id)
{
    setObjectName(QString("GalleryCell:%1").arg(id.toString()));
}

GalleryCell::GalleryCell(const Id &id, const QImage &orig, Gallery *parent)
    : QLabel{parent->widget()}
    , mpGallery(parent)
    , mBlank(false)
    , mIdent(id)
{
    setObjectName(QString("GalleryCell:%1").arg(id.toString()));
    generate(orig);
}

bool GalleryCell::isNull() const
{
    if (isBlank()) return true;
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

QPixmap GalleryCell::generate(const QImage &orig, const QColor border)
{
    QPixmap result(props().cellPixelSize());
    QPainter tPainter;
    Q_ASSERT(tPainter.begin(&result));
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
    QLabel::setPixmap(result);
    return mPixmap = result;
}

void GalleryCell::setBlank()
{
    qInfo() << Q_FUNC_INFO;
    QImage tImage(props().itemPixelSize(), QImage::Format_ARGB32);
    tImage.fill(props().itemForeground());
    generate(tImage);
    mBlank = true;
}

GalleryProperties GalleryCell::props() const { return gallery()->props(); }
GalleryProperties &GalleryCell::props() { return gallery()->props(); }

Uid GalleryCell::uid() const
{
    const Id cIdent = id();
    return cIdent.uid();
}
