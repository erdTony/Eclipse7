QT += widgets
TEMPLATE = lib
DEFINES += EIRGRAPHICS_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../libs.pri)
include(../../useCore.pri)
include(../../useMatgeo.pri)

SOURCES += \
    GraphicsScene.cpp \
    GraphicsView.cpp \
    eirGraphics.cpp

HEADERS += \
    GraphicsScene.h \
    GraphicsView.h \
    eirGraphics.h \
    eirGraphics_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
