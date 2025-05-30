QT += gui
TEMPLATE = lib
DEFINES += EIRCOLOR_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    eircolor.cpp

HEADERS += \
    eirColor_global.h \
    eircolor.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
