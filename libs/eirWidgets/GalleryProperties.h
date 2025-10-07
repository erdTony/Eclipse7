#pragma once
#include "eirWidgets.h"

#include <QSharedData>
#include <DataProperty.h>

#include <QColor>

#include <Size.h>
#include <Types.h>



#define GALLERY_DATAPROPS(TND) \
    TND(unsigned, modes, 0) \
    TND(Size, galleryPixelSize, Size()) \
    TND(Size, itemPixelSize, Size(128)) \
    TND(Size, cellPixelSize, Size(136)) \
    TND(Size, spacingSize, Size(4)) \
    TND(int, selectionWidth, 4) \
    TND(Size, galleryItems, Size()) \
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

public: // debug
    QStringList toDebugStrings(const QString &qfi=QString()) const;
};

inline int GalleryProperties::itemCols() const { return galleryItems().width(); }
inline int GalleryProperties::itemCount() const { return galleryItems().area(); }

