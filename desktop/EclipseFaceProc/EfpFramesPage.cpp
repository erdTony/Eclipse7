#include "EfpFramesPage.h"

#include <QDir>
#include <QFileInfoList>
#include <QFrame>
#include <QHBoxLayout>

#include <MainWindowPageStack.h>
#include <Gallery.h>
#include <GalleryProperties.h>
#include <Label.h>
#include <Url.h>

EfpFramesPage::EfpFramesPage(QWidget *parent)
    : BaseMainWindowPage{"Frames", parent}
    , mpFrameLabel(new Label(Size(512), Qt::darkGreen))
    , mpDetectLabel(new Label(Size(512), Qt::darkBlue))
    , mpGallery(new Gallery(this))
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("EFPFramesPage");
}

void EfpFramesPage::setup()
{
    qDebug() << Q_FUNC_INFO;
    setDefaultProperties();
    readSettingsProperties();
    props().calculateFromItems(Size(8, 1));
    qDebug() << props().galleryItems() << props().galleryPixelSize();

    pageGrid()->addWidget(mpFrameLabel, 0, 0, 1, 1);
    pageGrid()->addWidget(mpDetectLabel, 0, 1, 1, 1);

    int tWidth = mpFrameLabel->width() + mpDetectLabel->width();
    tWidth = qMax(tWidth, props().galleryPixelSize().width());
    int tHeight = qMax(mpFrameLabel->height(), mpDetectLabel->height());
    tHeight += props().galleryPixelSize().height();

    setSizes(QSizePolicy::MinimumExpanding, Size(tWidth, tHeight));
    gallery()->setup(props());
    pageGrid()->addWidget(gallery()->widget(), 1, 0, 1, 2);
    qDebug() << Q_FUNC_INFO << props().galleryPixelSize() << "exit";
}

void EfpFramesPage::activate()
{
    qDebug() << Q_FUNC_INFO;
}

void EfpFramesPage::start(const Url &url)
{
    qDebug() << Q_FUNC_INFO;
    const QDir cInputDir = url.dir();
    const QStringList cFileFilters = QStringList() << "*.jpg" << "*.png";
    const QFileInfoList cFIs = cInputDir.entryInfoList(cFileFilters);
    foreach (const QFileInfo cFI, cFIs)
    {
        QImage tFrame(cFI.filePath());
        if (tFrame.isNull()) continue;
        mpFrameLabel->set(mpFrameLabel->size(), tFrame);
        gallery()->add(tFrame);
    }
}

void EfpFramesPage::setDefaultProperties(const Size baseGallerySize)
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

void EfpFramesPage::readSettingsProperties()
{
    qDebug() << Q_FUNC_INFO;
    // TODO EFPFramesPage::readSettingsProperties()
}

