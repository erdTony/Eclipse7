#include "SandboxScene.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPoint>

#include <BaseImage.h>
#include <Size.h>

#include "SandboxMainWindow.h"

SandboxScene::SandboxScene(SandboxMainWindow *parent)
    : QGraphicsScene{parent}
    , mpMainWindow(parent)
    , mViewRect(Size(512, 512))
{
    qInfo() << Q_FUNC_INFO;
    setObjectName("SandboxScene");
}

SandboxScene::~SandboxScene()
{
    qInfo() << Q_FUNC_INFO;
    foreach (QGraphicsPixmapItem * pItem, mPixmapItems)
    {
        removeItem(pItem);
        delete pItem;
    }
}

void SandboxScene::initialize()
{
    qInfo() << Q_FUNC_INFO;
    mpView = new QGraphicsView(this);
    emit initialized();
}

void SandboxScene::configure()
{

    emit configured();
}

void SandboxScene::setup()
{
    qInfo() << Q_FUNC_INFO;
    view()->setMinimumSize(viewRect().size());
    view()->setMaximumSize(viewRect().size());
    view()->centerOn(viewRect().center());
    set(BackColor, Qt::green);
    emit setuped();
}

void SandboxScene::set(const Layer layer, const QColor &fill)
{
    qInfo() << Q_FUNC_INFO << layer;
    QPixmap tPixmap(viewRect().size());
    tPixmap.fill(fill);
    set(layer, tPixmap);
}

void SandboxScene::set(const Layer layer, const BaseImage &bi)
{
    qInfo() << Q_FUNC_INFO << layer;
    set(layer, bi.baseImage());
}

void SandboxScene::set(const Layer layer, const QImage &qi)
{
    qInfo() << Q_FUNC_INFO << layer;
    set(layer, QPixmap::fromImage(qi));
}

void SandboxScene::set(const Layer layer, const QPixmap &pm)
{
    qInfo() << Q_FUNC_INFO << layer;
    if (mPixmapItems.isEmpty())
        mPixmapItems.fill(nullptr, Layer::$max);
    QGraphicsPixmapItem * pOldItem = mPixmapItems[layer];
    QGraphicsPixmapItem * pNewItem = new QGraphicsPixmapItem(pm);
    if (pOldItem)
    {
        removeItem(pOldItem);
        delete pOldItem;
    }
    pNewItem->setVisible(true);
    pNewItem->setZValue(layer);
    addItem(pNewItem);
}

QWidget *SandboxScene::widget()
{
    return view()->viewport();
}


