#pragma once
#include "eirImage.h"

#include <GraphicsView.h>

class GalleryScene;

class EIRIMAGE_EXPORT GalleryView : public GraphicsView
{
    Q_OBJECT
public:
    GalleryView(GalleryScene * scene);
};
