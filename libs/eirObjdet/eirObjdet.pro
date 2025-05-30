QT -= gui
TEMPLATE = lib
DEFINES += EIROBJDET_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    eirobjdet.cpp

HEADERS += \
    eirObjdet_global.h \
    eirobjdet.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
