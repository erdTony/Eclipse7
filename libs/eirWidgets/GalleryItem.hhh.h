#pragma once

#include <Uid.h>

class GalleryItem
{
public: // ctors
    GalleryItem();
    GalleryItem(const QImage &qi, const Uid uid=Uid::generate83());

private:
    Uid mUid;
    QImage mOriginalImage;
    QImage mScaledImage;
    QPixmap mPixmap;
    QLabel * mpLabel;
};
