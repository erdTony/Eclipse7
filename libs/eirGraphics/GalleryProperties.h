#pragma once
#include "eirGraphics.h"

#include <QSharedData>
#include <DataProperty.h>

#include <Size.h>
#include <Types.h>


typedef unsigned GalleryOptions;

#define GALLERY_DATAPROPS(TND) \
    TND(Size, galleryPixelSize, Size()) \
    TND(GalleryOptions, options, 0) \
    TND(Size, itemSize, Size(256)) \
    TND(Size, spacingSize, Size(8)) \
    TND(Count, selectionWidth, 4) \
    TND(Size, itemsInFrame, Size()) \


class GalleryPropertiesData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(GALLERY_DATAPROPS);
public:
    GalleryPropertiesData(void)
    {
        DEFINE_DATAPROPS_CTORS(GALLERY_DATAPROPS);
    }
};

class EIRGRAPHICS_EXPORT GalleryProperties
{
    DECLARE_PARENT_DATAPROPS(GALLERY_DATAPROPS);
    DECLARE_DATAPROPS(GalleryProperties, GalleryPropertiesData);

public: // const
    int itemCols() const;
    int itemCount() const;

public: // non-const
    void calculateFromFrame(const Size frameSz,
                            const Size itemSz=Size(),
                            const Size spacingSz=Size());
    void calculateFromItems(const Size items,
                            const Size itemSz=Size(),
                            const Size spacingSz=Size());
};

inline int GalleryProperties::itemCols() const { return itemsInFrame().width(); }
inline int GalleryProperties::itemCount() const { return itemsInFrame().area(); }

