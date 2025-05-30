QT += widgets
TEMPLATE = lib
DEFINES += EIRWIDGETS_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    eirwidgets.cpp

HEADERS += \
    eirWidgets_global.h \
    eirwidgets.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
