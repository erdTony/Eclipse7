#include "EFPFramesPage.h"

#include <QHBoxLayout>

#include <Gallery.h>

EFPFramesPage::EFPFramesPage(MainWindowPageStack *pMWPS)
    : BaseMainWindowPage{"Frames", pMWPS}
    , mpGallery(new Gallery(this))
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("EFPFramesPage");
}

void EFPFramesPage::setup()
{
    //const Size cPageSize = QWidget::size();
    gallery()->props().calculateFromItems(Size(6, 2), Size(256), 8);
    gallery()->setup();
    QBoxLayout * pBox = new QHBoxLayout();
    pBox->addWidget(gallery()->widget());
    minimumSize(gallery()->props().galleryPixelSize().added(8));
    QWidget::setLayout(pBox);
    qDebug() << Q_FUNC_INFO << minimumSize();
}

