#include "Gallery.h"

#include "GalleryScene.h"
#include "GalleryView.h"

Gallery::Gallery(QWidget *parent)
    : QWidget{parent}
    , mpScene(new GalleryScene(this))
    , mpView(new GalleryView(mpScene))
{
    setObjectName("Gallery");
}



// =============== Properties ==============
