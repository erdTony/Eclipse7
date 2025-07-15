#include "Gallery.h"

#include <QBrush>
#include <QColor>
#include <QPalette>
#include <QPen>
#include <QGridLayout>

#include <SCRect.h>

#include "GalleryCell.h"
#include "GalleryFrame.h"
#include "GalleryGrid.h"

Gallery::Gallery(QWidget *parent)
    : QObject{parent}
    , mpFrame(new GalleryFrame(parent))
    , mpGrid(new GalleryGrid(this))
{
    setObjectName("Gallery");
}

void Gallery::setup(const GalleryProperties gp)
{
    mProperties = gp;
    const int cItemCount = props().itemCount();
    qInfo() << Q_FUNC_INFO << gp.modes() << cItemCount;

    frame()->setMinimumSize(props().framePixelSize().expanded(16));

    QPalette tPalette;
    tPalette.setColor(QPalette::Window, props().frameBackground());
    tPalette.setColor(QPalette::WindowText, props().frameForeground());
    frame()->setPalette(tPalette);
    frame()->setAutoFillBackground(true);
    frame()->setFrameStyle(props().frameStyle());
    frame()->setLineWidth(4);

    GalleryGrid * pGrid = new GalleryGrid(this);
    GalleryCell * pCell = new GalleryCell(this);
    // TODO different pCell = pCell->blankCell()
    pCell = pCell->blankCell();
    pGrid->setup(props().itemsInFrame(), pCell);
    frame()->setLayout(pGrid->layout());
}

void Gallery::set(const Point pt, GalleryCell *pCell)
{
    qInfo() << Q_FUNC_INFO << pt << pCell->ident();
    // TODO Gallery::set(): grid()->set(pt, pCell);
}
