QT += gui
TEMPLATE = lib
DEFINES += EIRGUI_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    eirgui.cpp

HEADERS += \
    eirGui_global.h \
    eirgui.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
