QT -= gui
TEMPLATE = lib
DEFINES += EIRFACEBASE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    eirFacebase.cpp

HEADERS += \
    eirFacebase_global.h \
    eirFacebase.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
