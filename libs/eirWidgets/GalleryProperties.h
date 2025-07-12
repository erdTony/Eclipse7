#pragma once
#include "eirWidgets.h"

#include <QSharedData>
#include <DataProperty.h>

#include <QFrame>

#include <Size.h>
#include <Types.h>



#define GALLERY_DATAPROPS(TND) \
    TND(Size, framePixelSize, Size()) \
    TND(unsigned, modes, 0x11) \
    TND(Size, itemPixelSize, Size(256)) \
    TND(Size, cellPixelSize, Size(272)) \
    TND(Size, spacingSize, Size(8)) \
    TND(Count, selectionWidth, 4) \
    TND(Size, itemsInFrame, Size()) \
    TND(int, frameShape, QFrame::Box) \
    TND(QColor, frameForeground, QColor(128, 128, 192)) \
    TND(QColor, frameBackground, QColor(128, 128, 160)) \
    TND(QColor, itemForeground, QColor(64, 64, 192)) \
    TND(QColor, itemBackground, QColor(64, 64, 160)) \





class GalleryPropertiesData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(GALLERY_DATAPROPS);
public:
    GalleryPropertiesData(void)
    {
        DEFINE_DATAPROPS_CTORS(GALLERY_DATAPROPS);
    }
};

class EIRWIDGETS_EXPORT GalleryProperties
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

