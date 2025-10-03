#include "Gallery.h"

#include <QBrush>
#include <QColor>
#include <QPalette>
#include <QPen>
#include <QGridLayout>

#include <SCRect.h>

#include "GalleryCell.h"
#include "GalleryGrid.h"

Gallery::Gallery(QWidget *parent)
    : QObject{parent}
    , mpGrid(new GalleryGrid(this))
    , mpGalleryWidget(new QWidget(parent))
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("Gallery");
}

void Gallery::setup(const GalleryProperties gp)
{
    mProperties = gp;
    qInfo() << Q_FUNC_INFO << gp.modes(); // << gp.toDebugStrings();

    grid()->setup(props().galleryItems());
    widget()->setLayout(grid()->layout());
}

void Gallery::add(const QImage &qi)
{
    qDebug() << Q_FUNC_INFO;
    GalleryCell * pCell = grid()->cell(mCurrentIndex);
    pCell->generate(qi);
    mCurrentIndex = ++mCurrentIndex % grid()->count();
}

void Gallery::set(const Point pt, GalleryCell *pCell)
{
    qInfo() << Q_FUNC_INFO << pt << pCell->id();
    // TODO Gallery::set(): grid()->set(pt, pCell);
}
