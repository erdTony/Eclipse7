#include "Gallery.h"

#include <QBrush>
#include <QColor>
#include <QPen>
#include <QGridLayout>

#include <SCRect.h>

#include "GalleryFrame.h"

Gallery::Gallery(QWidget *parent)
    : QObject{parent}
    , mpFrame(new GalleryFrame(parent))
{
    setObjectName("Gallery");
}

void Gallery::setup()
{
    qInfo() << Q_FUNC_INFO;
    frame()->setMinimumSize(props().framePixelSize().expanded(16));

    QGridLayout * pGridLayout = new QGridLayout();
    frame()->setLayout(pGridLayout);

    const int cItemCount = props().itemCount();
    for (Index ix = 0; ix < cItemCount;  ++ix)
    {
        const Point cItemPoint(props().itemsInFrame(), ix);
    }
}

