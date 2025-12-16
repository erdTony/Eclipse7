QT += gui
TEMPLATE = lib
DEFINES += EIRGUI_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)
include(../../useCore.pri)
include(../../useMatgeo.pri)

SOURCES += \
    Icon.cpp \
    IconLibrary.cpp \
    IconManager.cpp \
    eirGui.cpp

HEADERS += \
    Icon.h \
    IconLibrary.h \
    IconManager.h \
    eirGui.h \
    eirGui_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
