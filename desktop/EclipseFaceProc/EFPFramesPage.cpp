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
    props().itemsInFrame(Size(2, 1));
    props().calculateFromFrame(pageStack()->minimumSize(),
                               Size(256), Size(8));
    props().calculateFromItems(props().itemsInFrame());
    qDebug() << props().itemsInFrame() << props().framePixelSize();
    setSize(QSizePolicy::MinimumExpanding, props().framePixelSize());

    gallery()->setup(props());

    QBoxLayout * pBox = new QHBoxLayout();
    pBox->addWidget(gallery()->widget());
    QWidget::setMinimumSize(props().framePixelSize().expanded(8));
    QWidget::setLayout(pBox);
    qDebug() << Q_FUNC_INFO << minimumSize() << "exit";
}

void EFPFramesPage::setDefaultProperties()
{
    qDebug() << Q_FUNC_INFO;
    props().modes(Gallery::RollingRow | Gallery::AlignTop);
    props().itemPixelSize(Size(256));
    props().cellPixelSize(props().itemPixelSize() + 16);
    props().spacingSize(Size(8));
    props().selectionWidth(4);
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

