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

void GalleryGrid::setup(const Size sz)
{
    qInfo() << Q_FUNC_INFO << sz;
    const Size cCellSize = gallery()->props().cellPixelSize();
    for (Index row = 0; row < sz.height(); ++row)
        mGrid.setRowMinimumHeight(row, cCellSize.height());
    for (Index col = 0; col < sz.width(); ++col)
        mGrid.setColumnMinimumWidth(col, cCellSize.width());
    for (Index row = 0; row < sz.height(); ++row)
        for (Index col = 0; col < sz.width(); ++col)
        {
            GalleryCell * pCell = new GalleryCell(true, gallery());
            pCell->setBlank();
            mGrid.addWidget(pCell, row, col, Qt::AlignCenter);
            qDebug() << row << col << pCell->geometry()
                << pCell->pixmap().size() << mGrid.cellRect(row, col);
        }
}
