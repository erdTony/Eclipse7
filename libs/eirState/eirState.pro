QT -= gui
TEMPLATE = lib
DEFINES += EIRSTATE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../eirBase.pri)

SOURCES += \
    eirstate.cpp

HEADERS += \
    eirState_global.h \
    eirstate.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
