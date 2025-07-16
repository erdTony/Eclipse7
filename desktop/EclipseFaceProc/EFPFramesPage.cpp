#include "EFPFramesPage.h"

#include <QFrame>
#include <QHBoxLayout>

#include <MainWindowPageStack.h>
#include <Gallery.h>
#include <GalleryProperties.h>

EFPFramesPage::EFPFramesPage(MainWindowPageStack *pMWPS)
    : BaseMainWindowPage{"Frames", pMWPS}
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
    qDebug() << props().itemsInFrame() << props().framePixelSize();
    setSize(QSizePolicy::MinimumExpanding, props().framePixelSize());

    gallery()->setup(props());

    QBoxLayout * pBox = new QHBoxLayout(); Q_CHECK_PTR(pBox);
    QWidget::setLayout(pBox);
    pBox->addWidget(gallery()->widget());
    qDebug() << Q_FUNC_INFO << props().framePixelSize() << "exit";
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
    props().frameStyle(QFrame::Box);
    props().frameForeground(QColor(128, 128, 192));
    props().frameBackground(QColor(128, 128, 160));
    props().itemForeground(QColor(64, 64, 192));
    props().itemBackground(QColor(64, 64, 160));
}

void EFPFramesPage::readSettingsProperties()
{
    qDebug() << Q_FUNC_INFO;
    // TODO EFPFramesPage::readSettingsProperties()
}

