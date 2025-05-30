QT -= gui
TEMPLATE = lib
DEFINES += EIRBASE_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)

SOURCES += \
    eirbase.cpp

HEADERS += \
    eirBase_global.h \
    eirbase.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
