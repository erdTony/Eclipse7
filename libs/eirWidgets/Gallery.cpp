#include "Gallery.h"

#include <QBrush>
#include <QColor>
#include <QGraphicsRectItem>
#include <QPen>
#include <QVBoxLayout>

#include <SCRect.h>

#include "GalleryFrame.h"
#include "GalleryScene.h"
#include "GalleryView.h"

Gallery::Gallery(QWidget *parent)
    : QObject{parent}
    , mpFrame(new GalleryFrame(parent))
    , mpScene(new GalleryScene())
    , mpView(new GalleryView())
{
    setObjectName("Gallery");
}

void Gallery::setup()
{
    qInfo() << Q_FUNC_INFO;
    frame()->setMinimumSize(props().galleryPixelSize().expanded(16));
    QGraphicsRectItem * pFrameItem =
        scene()->addRect(SCRect(props().galleryPixelSize()),
                     QPen(), QBrush(QColor(48, 48, 64)));
    pFrameItem->setZValue(100);
    view()->setScene(scene());
    view()->centerOn(props().galleryPixelSize().center());
    QVBoxLayout * pViewLayout = new QVBoxLayout();
    pViewLayout->addWidget(view());
    frame()->setLayout(pViewLayout);
    mItemRectMatrix = RectMatrix(props().itemsInFrame());
    const int cItemCount = props().itemCount();
    for (Index ix = 0; ix < cItemCount;  ++ix)
    {
        const Point cItemPoint(props().itemsInFrame(), ix);
        const int cItemRow = props().spacingSize().height()
                 + (cItemPoint.row()
                    * (props().spacingSize().height() + props().itemSize().height()));
        const int cItemCol = props().spacingSize().width()
                 + (cItemPoint.col()
                    * (props().spacingSize().width() + props().itemSize().width()));
        const SCRect cItemRect = SCRect(props().itemSize()) + Point(cItemCol, cItemRow);
        mItemRectMatrix[ix] = cItemRect;
        qDebug() << ix << props().itemsInFrame()
                 << cItemPoint << cItemRect.toDebugString();
        QGraphicsRectItem * pItemItem =
            scene()->addRect(cItemRect, QPen(), QBrush(QColor(Qt::blue)));
        pItemItem->setZValue(150);
    }
}

