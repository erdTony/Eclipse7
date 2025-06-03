QT -= gui
TEMPLATE = lib
DEFINES += EIRTYPE_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri))

SOURCES += \
    eirtype.cpp

HEADERS += \
    eirType_global.h \
    eirtype.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
