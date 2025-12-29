#include "EfpFramesPage.h"

#include <QDir>
#include <QFileInfoList>
#include <QFrame>
#include <QHBoxLayout>

#include <MainWindowPageStack.h>
//#include <Gallery.h>
#include <Label.h>
#include <Log.h>
#include <Url.h>

#include "EfpApplication.h"
#include "EfpImageReader.h"

EfpFramesPage::EfpFramesPage(QWidget *parent)
    : BaseMainWindowPage{"Frames", parent}
    , mpImageReader(new EfpImageReader(this))
    , mpFrameLabel(new Label(Size(512), Qt::darkGreen))
    , mpDetectLabel(new Label(Size(512), Qt::darkBlue))
//    , mpGallery(new Gallery(this))
{
    FNENTER();
    setObjectName("EFPFramesPage");
    reader()->initialize();
}

void EfpFramesPage::setup()
{
    FNSLOT();
    setDefaultProperties();
    readSettingsProperties();
    pageGrid()->addWidget(mpFrameLabel, 0, 0, 1, 1);
    pageGrid()->addWidget(mpDetectLabel, 0, 1, 1, 1);
    reader()->pause();
    reader()->setup();
    connect(APP, &EfpApplication::paused, reader(), &EfpImageReader::pause);
    connect(APP, &EfpApplication::resumed, reader(), &EfpImageReader::resume);
    connect(reader(), &EfpImageReader::captured,
            this, &EfpFramesPage::hasCaptured);
    /*
    props().calculateFromItems(Size(8, 1));
    qDebug() << props().galleryItems() << props().galleryPixelSize();


    int tWidth = mpFrameLabel->width() + mpDetectLabel->width();
    tWidth = qMax(tWidth, props().galleryPixelSize().width());
    int tHeight = qMax(mpFrameLabel->height(), mpDetectLabel->height());
    tHeight += props().galleryPixelSize().height();

    setSizes(QSizePolicy::MinimumExpanding, Size(tWidth, tHeight));
    gallery()->setup(props());
    pageGrid()->addWidget(gallery()->widget(), 1, 0, 1, 2);
    qDebug() << Q_FUNC_INFO << props().galleryPixelSize() << "exit";
    */
}

void EfpFramesPage::activate()
{
    FNSLOT();
}

void EfpFramesPage::start(const QDir &dir)
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO << dir.path();
    reader()->start(dir);
}

void EfpFramesPage::hasCaptured(const FileInfo &fi, const QImage qi)
{
    FNSLOT();
    UNUSED(fi); // TODO StatusBar
    // TODO FaceDetect heat map
    QImage tGreyImage = qi.convertedTo(QImage::Format_Grayscale8);
    mpDetectLabel->set(mpFrameLabel->size(), qi);
    mpFrameLabel->set(mpDetectLabel->size(), tGreyImage);
}

void EfpFramesPage::setDefaultProperties(const Size baseGallerySize)
{
    FNENTER();
    UNUSED(baseGallerySize);
    /*
    props().modes(Gallery::RollingRow | Gallery::AlignTop);
    props().itemPixelSize(baseGallerySize);
    props().cellPixelSize(props().itemPixelSize()
                              .expanded(baseGallerySize / 16));
    props().spacingSize(Size(baseGallerySize / 16));
    props().selectionWidth(baseGallerySize.max() / 32);
    props().itemForeground(QColor(64, 64, 192));
    props().itemBackground(QColor(64, 64, 160));
    */
}

void EfpFramesPage::readSettingsProperties()
{
    FNENTER();
    // TODO EFPFramesPage::readSettingsProperties()
}

