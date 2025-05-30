QT -= gui
TEMPLATE = lib
DEFINES += EIRQTCV_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    eirqtcv.cpp

HEADERS += \
    eirQtCV_global.h \
    eirqtcv.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
