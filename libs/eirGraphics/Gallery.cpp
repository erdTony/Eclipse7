#include "Gallery.h"

#include <QGuiApplication>
#include <QPalette>

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
    frame()->setMinimumSize(props().galleryPixelSize().added(8));
    QPalette tFramePalette = QGuiApplication::palette();
    tFramePalette.setColor(QPalette::Window, QColor(160, 160, 255));
    frame()->setPalette(tFramePalette);
    frame()->setFrameStyle(QFrame::Panel | QFrame::Raised);
    frame()->setLineWidth(4);
}

