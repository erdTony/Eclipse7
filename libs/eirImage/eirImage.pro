QT += gui
TEMPLATE = lib
DEFINES += EIRIMAGE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)
include(../../useBase.pri)
include(../../useMatgeo.pri)
include(../../useColor.pri)

SOURCES += \
    BaseImage.cpp \
    BasePixel32.cpp \
    BasePixelBehavior.cpp \
    ColorImage.cpp \
    Grey16Image.cpp \
    GreyImage.cpp \
    Image.cpp \
    IndexedImage.cpp \
    PixmapStack.cpp \
    SupportedFormats.cpp \
    ThumbImage.cpp \
    eirImage.cpp

HEADERS += \
    BaseImage.h \
    BasePixel32.h \
    BasePixelBehavior.h \
    ColorImage.h \
    Grey16Image.h \
    GreyImage.h \
    Image.h \
    IndexedImage.h \
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
