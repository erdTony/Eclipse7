#include "GalleryProperties.h"

#include <QtDebug>

#include "Gallery.h"

DEFINE_DATAPROPS(GalleryProperties, GalleryPropertiesData);

void GalleryProperties::ctor(void) {;}
void GalleryProperties::dtor(void) {;}

void GalleryProperties::calculateFromFrame(const Size frameSz,
                                           const Size itemSz,
                                           const Size spacingSz)
{
    if (itemSz) itemPixelSize(itemSz);
    if (spacingSz) spacingSize(spacingSz);
    cellPixelSize(itemPixelSize().expanded(16));
    const Size cItemSize = itemPixelSize();
    const Size cSpacingSize = spacingSize();
    unsigned tPixelWidth  = frameSz.width()  - cSpacingSize.width();
    unsigned tPixelHeight = frameSz.height() - cSpacingSize.height();

    unsigned tItemsAcross = tPixelWidth  / (cItemSize.width()  + cSpacingSize.width());
    unsigned tItemsDown   = tPixelHeight / (cItemSize.height() + cSpacingSize.height());
    if (modes() & Gallery::RollingRow) tItemsDown = 1;
    if (modes() & Gallery::RollingCol) tItemsAcross = 1;
    itemsInFrame(Size(tItemsAcross, tItemsDown));

    tPixelWidth = itemsInFrame().width() * cellPixelSize().width()
                  + (itemsInFrame().width() + 1) * spacingSize().width();
    tPixelHeight = tItemsDown * cellPixelSize().height()
                  + (tItemsDown + 1) * spacingSize().height();
    galleryPixelSize(Size(tPixelWidth, tPixelHeight));
    framePixelSize(Size(tPixelWidth + 8, tPixelHeight + 8));
    qInfo() << Q_FUNC_INFO << frameSz
            << itemPixelSize() << spacingSize()
            << tPixelWidth << tPixelHeight
            << itemsInFrame() << galleryPixelSize()
            << framePixelSize() << cellPixelSize();
}

void GalleryProperties::calculateFromItems(const Size items,
                                           const Size itemSz,
                                           const Size spacingSz)
{
    if (spacingSz) spacingSize(spacingSz);
    if (itemSz) itemPixelSize(itemSz);
    itemsInFrame(items);
    const Size cSpacingSize = spacingSize();
    const Size cItemSize = itemPixelSize();
    const uint cPixelWidth = cSpacingSize.width() + items.width()
                                                        * (cItemSize.width() + cSpacingSize.width());
    const uint cPixelHeight = cSpacingSize.height() + items.height()
                                                          * (cItemSize.height() + cSpacingSize.height());
    framePixelSize(Size(cPixelWidth, cPixelHeight));
    qInfo() << Q_FUNC_INFO << itemsInFrame() << itemPixelSize() << spacingSize()
            << cPixelWidth << cPixelHeight
            << framePixelSize();
}
