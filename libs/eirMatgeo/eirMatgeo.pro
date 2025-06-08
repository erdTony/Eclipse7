QT -= gui
TEMPLATE = lib
DEFINES += EIRMATGEO_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)
include (../../useBase.pri)

SOURCES += \
    SCLine.cpp \
    SCRect.cpp \
    eirmatgeo.cpp

HEADERS += \
    SCLine.h \
    SCRect.h \
    eirMatgeo_global.h \
    eirmatgeo.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
