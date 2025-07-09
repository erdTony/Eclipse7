#include "GalleryProperties.h"

DEFINE_DATAPROPS(GalleryProperties, GalleryPropertiesData);

void GalleryProperties::ctor(void) {;}
void GalleryProperties::dtor(void) {;}

void GalleryProperties::calculateFromFrame(const Size frameSz,
                                           const Size itemSz,
                                           const Size spacingSz)
{
    if (spacingSz) spacingSize(spacingSz);
    if (itemSz) itemSize(itemSz);
    const Size cSpacingSize = spacingSize();
    const Size cItemSize = itemSize();
    const uint cPixelWidth = frameSz.width() - cSpacingSize.width();
    const uint cPixelHeight = frameSz.height() - cSpacingSize.height();
    const uint cItemsAcross = cPixelWidth / (cItemSize.width() + cSpacingSize.width());
    const uint cItemsDown = cPixelHeight / (cItemSize.height() + cSpacingSize.height());
    itemsInFrame(Size(cItemsAcross, cItemsDown));
}

void GalleryProperties::calculateFromItems(const Size items,
                                           const Size itemSz,
                                           const Size spacingSz)
{
    if (spacingSz) spacingSize(spacingSz);
    if (itemSz) itemSize(itemSz);
    itemsInFrame(items);
    const Size cSpacingSize = spacingSize();
    const Size cItemSize = itemSize();
    const uint cPixelWidth = cSpacingSize.width() + items.width()
                            * (cItemSize.width() + cSpacingSize.width());
    const uint cPixelHeight = cSpacingSize.height() + items.height()
                            * (cItemSize.height() + cSpacingSize.height());
    galleryPixelSize(Size(cPixelWidth, cPixelHeight));
}
