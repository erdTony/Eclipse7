# QT -= gui
TEMPLATE = lib
DEFINES += EIRSVG_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../libs.pri)

SOURCES += \
    SvgRender.cpp \
    eirsvg.cpp

HEADERS += \
    SvgRender.h \
    eirSvg_global.h \
    eirsvg.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
