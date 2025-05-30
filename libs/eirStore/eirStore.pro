QT -= gui
TEMPLATE = lib
DEFINES += EIRSTORE_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    eirstore.cpp

HEADERS += \
    eirStore_global.h \
    eirstore.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
