QT += gui \
    widgets
TEMPLATE = lib
DEFINES += EIRIMAGE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)
include(../../useBase.pri)
include(../../useType.pri)
include(../../useMatgeo.pri)
include(../../useColor.pri)
include(../../useGraphics.pri)

SOURCES += \
    BaseImage.cpp \
    BaseImageCache.cpp \
    BasePixel32.cpp \
    BasePixelBehavior.cpp \
    ColorImage.cpp \
    Gallery.cpp \
    GalleryPixmap.cpp \
    GalleryScene.cpp \
    GalleryView.cpp \
    Grey16Image.cpp \
    GreyImage.cpp \
    Image.cpp \
    ImageCacheEntry.cpp \
    ImageCacheItem.cpp \
    ImageClass.cpp \
    ImageEncoding.cpp \
    ImageObject.cpp \
    ImageSet.cpp \
    ImageType.cpp \
    ImageUid.cpp \
    IndexedImage.cpp \
    MemoryImageCache.cpp \
    PixmapStack.cpp \
    SupportedFormats.cpp \
    ThumbImage.cpp \
    eirImage.cpp

HEADERS += \
    BaseImage.h \
    BaseImageCache.h \
    BasePixel32.h \
    BasePixelBehavior.h \
    ColorImage.h \
    Gallery.h \
    GalleryPixmap.h \
    GalleryScene.h \
    GalleryView.h \
    Grey16Image.h \
    GreyImage.h \
    Image.h \
    ImageCacheEntry.h \
    ImageCacheItem.h \
    ImageClass.h \
    ImageEncoding.h \
    ImageObject.h \
    ImageSet.h \
    ImageType.h \
    ImageUid.h \
    IndexedImage.h \
    MemoryImageCache.h \
    PixmapStack.h \
    SupportedFormats.h \
    ThumbImage.h \
    eirImage.h \
    eirImage_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
