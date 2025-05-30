QT -= gui
TEMPLATE = lib
DEFINES += EIRFACEREC_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    eirfacerec.cpp

HEADERS += \
    eirFacerec_global.h \
    eirfacerec.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
