QT += widgets
TEMPLATE = lib
DEFINES += EIRGRAPHICS_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../libs.pri)
include(../../useBase.pri)
include(../../useType.pri)
include(../../useMatgeo.pri)
include(../../useImage.pri)


SOURCES += \
    Gallery.cpp \
    GalleryFrame.cpp \
    GalleryProperties.cpp \
    GalleryScene.cpp \
    GalleryView.cpp \
    eirGraphics.cpp

HEADERS += \
    Gallery.h \
    GalleryFrame.h \
    GalleryProperties.h \
    GalleryScene.h \
    GalleryView.h \
    eirGraphics.h \
    eirGraphics_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
