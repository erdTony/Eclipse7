QT -= gui
QT *= network
QT *= statemachine
QT *= sql
QT *= xml
TEMPLATE = lib
DEFINES += EIRLOGGER_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)

CPPFLAGS *= -E -Dm

SOURCES += \

HEADERS += \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
