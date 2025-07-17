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
    qInfo() << Q_FUNC_INFO << frameSz << itemSz << spacingSz;
//            << toDebugStrings();
    if ( ! itemSz.isEmpty()) itemPixelSize(itemSz);
    if ( ! spacingSz.isEmpty()) spacingSize(spacingSz);
    cellPixelSize(itemPixelSize().expanded(16));
    const Size cItemSize = itemPixelSize();
    const Size cSpacingSize = spacingSize();
    unsigned tPixelWidth  = frameSz.width()  - cSpacingSize.width();
    unsigned tPixelHeight = frameSz.height() - cSpacingSize.height();
//    qDebug() << tPixelWidth << tPixelHeight << toDebugStrings("before divide");
    Q_ASSERT( ! cItemSize.isEmpty()); Q_ASSERT( ! cSpacingSize.isEmpty());
    unsigned tItemsAcross = tPixelWidth  / (cItemSize.width()  + cSpacingSize.width());
    unsigned tItemsDown   = tPixelHeight / (cItemSize.height() + cSpacingSize.height());
    if (modes() & Gallery::RollingRow) tItemsDown = 1;
    if (modes() & Gallery::RollingCol) tItemsAcross = 1;
    galleryItems(Size(tItemsAcross, tItemsDown));

    tPixelWidth = galleryItems().width() * cellPixelSize().width()
                  + (galleryItems().width() + 1) * spacingSize().width();
    tPixelHeight = tItemsDown * cellPixelSize().height()
                  + (tItemsDown + 1) * spacingSize().height();
    galleryPixelSize(Size(tPixelWidth, tPixelHeight));
//    qDebug() << Q_FUNC_INFO << "exit" << frameSz
  //           << tPixelWidth << tPixelHeight << toDebugStrings("exit");
}

void GalleryProperties::calculateFromItems(const Size items,
                                           const Size itemSz,
                                           const Size spacingSz)
{
    if (spacingSz.isValid()) spacingSize(spacingSz);
    if (itemSz.isValid()) itemPixelSize(itemSz);
    galleryItems(items);
    const Size cSpacingSize = spacingSize();
    const Size cItemSize = itemPixelSize();
    const uint cPixelWidth = cSpacingSize.width() + items.width()
                                                        * (cItemSize.width() + cSpacingSize.width());
    const uint cPixelHeight = cSpacingSize.height() + items.height()
                                                          * (cItemSize.height() + cSpacingSize.height());
    qInfo() << Q_FUNC_INFO << galleryItems() << itemPixelSize() << spacingSize()
            << cPixelWidth << cPixelHeight;
}

QStringList GalleryProperties::toDebugStrings(const QString &qfi) const
{
    QStringList results;
    results << QString("{GalleryProperties: %1>").arg(qfi);
    results << QString("   modes:               %1").arg(modes());
    results << QString("   galleryPixelSize:    %1x%2").arg(galleryPixelSize().width()).arg(galleryPixelSize().height());
    results << QString("   itemPixelSize:       %1x%2").arg(itemPixelSize().width()).arg(itemPixelSize().height());
    results << QString("   cellPixelSize:       %1x%2").arg(cellPixelSize().width()).arg(cellPixelSize().height());
    results << QString("   spacingSize:         %1x%2").arg(spacingSize().width()).arg(spacingSize().height());
    results << QString("   selectionWidth:      %1").arg(selectionWidth());
    results << QString("   galleryItems:        %1x%2").arg(galleryItems().width()).arg(galleryItems().height());
    results << QString("   itemForeground:      %1").arg(itemForeground().name());
    results << QString("   itemBackground:      %1").arg(itemBackground().name());
    results << "<GalleryProperties}";
    return results;
}
