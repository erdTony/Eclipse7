QT += gui
TEMPLATE = lib
DEFINES += EIRIMAGE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

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
    eirimage.cpp

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
    eirImage_global.h \
    eirimage.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
