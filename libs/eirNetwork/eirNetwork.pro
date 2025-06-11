QT -= gui
TEMPLATE = lib
DEFINES += EIRNETWORK_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../../useBase.pri)

SOURCES += \
    Url.cpp \
    eirnetwork.cpp

HEADERS += \
    Url.h \
    eirNetwork_global.h \
    eirnetwork.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
