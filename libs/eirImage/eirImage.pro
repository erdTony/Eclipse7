QT += gui
TEMPLATE = lib
DEFINES += EIRIMAGE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    eirimage.cpp

HEADERS += \
    eirImage_global.h \
    eirimage.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
