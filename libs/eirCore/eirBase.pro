QT += core
QT += gui
QT += widgets
QT += network
TEMPLATE = lib
DEFINES += EIRBASE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)

SOURCES += \

HEADERS += \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
