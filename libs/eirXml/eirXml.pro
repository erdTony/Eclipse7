QT -= gui
TEMPLATE = lib
DEFINES += EIRXML_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    eirxml.cpp

HEADERS += \
    eirXml_global.h \
    eirxml.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
