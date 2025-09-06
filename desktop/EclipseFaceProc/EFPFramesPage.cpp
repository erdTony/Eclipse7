#include "EFPFramesPage.h"

#include <QDir>
#include <QFileInfoList>
#include <QFrame>
#include <QHBoxLayout>

#include <MainWindowPageStack.h>
#include <Gallery.h>
#include <GalleryProperties.h>
#include <Label.h>
#include <Url.h>

EFPFramesPage::EFPFramesPage(MainWindowPageStack *pMWPS)
    : BaseMainWindowPage{"Frames", pMWPS}
    , mpFrameLabel(new Label(Size(512), Qt::darkGreen))
    , mpDetectLabel(new Label(Size(512), Qt::darkBlue))
    , mpGallery(new Gallery(this))
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("EFPFramesPage");
}

void EFPFramesPage::setup()
{
    qDebug() << Q_FUNC_INFO << pageStack()->minimumSize();
    setDefaultProperties();
    readSettingsProperties();
    props().calculateFromFrame(pageStack()->minimumSize());
    qDebug() << props().galleryItems() << props().galleryPixelSize();

    pageGrid()->addWidget(mpFrameLabel, 0, 0, 1, 1);
    pageGrid()->addWidget(mpDetectLabel, 0, 1, 1, 1);

    //setSize(QSizePolicy::MinimumExpanding, props().galleryPixelSize());
    gallery()->setup(props());
    pageGrid()->addWidget(gallery()->widget(), 1, 0, 1, 2);
    qDebug() << Q_FUNC_INFO << props().galleryPixelSize() << "exit";
}

void EFPFramesPage::start(const Url &url)
{
    const QDir cInputDir = url.dir();
    const QStringList cFileFilters = QStringList() << "*.jpg" << "*.png";
    const QFileInfoList cFIs = cInputDir.entryInfoList(cFileFilters);
    foreach (const QFileInfo cFI, cFIs)
    {
        QImage tFrame(cFI.filePath());
        if (tFrame.isNull()) continue;
        gallery()->add(tFrame);
    }
}

void EFPFramesPage::setDefaultProperties(const Size baseGallerySize)
{
    qDebug() << Q_FUNC_INFO;
    props().modes(Gallery::RollingRow | Gallery::AlignTop);
    props().itemPixelSize(baseGallerySize);
    props().cellPixelSize(props().itemPixelSize()
                              .expanded(baseGallerySize / 16));
    props().spacingSize(Size(baseGallerySize / 16));
    props().selectionWidth(baseGallerySize.max() / 32);
    props().itemForeground(QColor(64, 64, 192));
    props().itemBackground(QColor(64, 64, 160));
}

void EFPFramesPage::readSettingsProperties()
{
    qDebug() << Q_FUNC_INFO;
    // TODO EFPFramesPage::readSettingsProperties()
}

