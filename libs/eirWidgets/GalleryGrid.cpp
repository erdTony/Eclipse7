#include "GalleryGrid.h"

#include <Point.h>
#include <Size.h>

#include "Gallery.h"
#include "GalleryCell.h"

GalleryGrid::GalleryGrid(Gallery *parent)
    : QObject{parent->widget()}
    , mpGallery(parent)
{
    setObjectName("GalleryGrid");
}

void GalleryGrid::setup(const Size sz, GalleryCell *pCell)
{
    qInfo() << Q_FUNC_INFO << sz << pCell->ident();

    for (Index row = 0; row < sz.height(); ++row)
        mGrid.setRowMinimumHeight(row, pCell->rect().height());
    for (Index col = 0; col < sz.width(); ++col)
        mGrid.setColumnMinimumWidth(col, pCell->rect().width());
    for (Index row = 0; row < sz.height(); ++row)
        for (Index col = 0; col < sz.width(); ++col)
            mGrid.addWidget(pCell, row, col, Qt::AlignCenter);
}
