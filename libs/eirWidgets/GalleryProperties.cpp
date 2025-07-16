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
    itemsInFrame(Size(tItemsAcross, tItemsDown));

    tPixelWidth = itemsInFrame().width() * cellPixelSize().width()
                  + (itemsInFrame().width() + 1) * spacingSize().width();
    tPixelHeight = tItemsDown * cellPixelSize().height()
                  + (tItemsDown + 1) * spacingSize().height();
    galleryPixelSize(Size(tPixelWidth, tPixelHeight));
    framePixelSize(Size(tPixelWidth + 8, tPixelHeight + 8));
//    qDebug() << Q_FUNC_INFO << "exit" << frameSz
  //           << tPixelWidth << tPixelHeight << toDebugStrings("exit");
}

void GalleryProperties::calculateFromItems(const Size items,
                                           const Size itemSz,
                                           const Size spacingSz)
{
    if (spacingSz.isValid()) spacingSize(spacingSz);
    if (itemSz.isValid()) itemPixelSize(itemSz);
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

QStringList GalleryProperties::toDebugStrings(const QString &qfi) const
{
    QStringList results;
    results << QString("{GalleryProperties: %1>").arg(qfi);
    results << QString("   framePixelSize:      %1x%2").arg(framePixelSize().width()).arg(framePixelSize().height());
    results << QString("   frameStyle:          %1").arg(frameStyle());
    results << QString("   frameForeground:     %1").arg(frameForeground().name());
    results << QString("   frameBackground:     %1").arg(frameBackground().name());
    results << QString("   modes:               %1").arg(modes());
    results << QString("   galleryPixelSize:    %1x%2").arg(galleryPixelSize().width()).arg(galleryPixelSize().height());
    results << QString("   itemPixelSize:       %1x%2").arg(itemPixelSize().width()).arg(itemPixelSize().height());
    results << QString("   cellPixelSize:       %1x%2").arg(cellPixelSize().width()).arg(cellPixelSize().height());
    results << QString("   spacingSize:         %1x%2").arg(spacingSize().width()).arg(spacingSize().height());
    results << QString("   selectionWidth:      %1").arg(selectionWidth());
    results << QString("   itemsInFrame:        %1x%2").arg(itemsInFrame().width()).arg(itemsInFrame().height());
    results << QString("   itemForeground:      %1").arg(itemForeground().name());
    results << QString("   itemBackground:      %1").arg(itemBackground().name());
    results << "<GalleryProperties}";
    return results;
}
