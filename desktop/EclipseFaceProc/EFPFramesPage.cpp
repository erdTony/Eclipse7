#include "EFPFramesPage.h"

#include <QHBoxLayout>

#include <MainWindowPageStack.h>
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
    gallery()->props().itemsInFrame(Size(2, 1));
    gallery()->props().modes(Gallery::RollingRow | Gallery::AlignTop);
    gallery()->props().calculateFromFrame(pageStack()->clientSize(), Size(256), Size(8));
    gallery()->props().calculateFromItems(gallery()->props().itemsInFrame());
    gallery()->setup();
    QBoxLayout * pBox = new QHBoxLayout();
    pBox->addWidget(gallery()->widget());
    minimumSize(gallery()->props().framePixelSize().expanded(8));
    QWidget::setLayout(pBox);
    qDebug() << Q_FUNC_INFO << minimumSize();
}

