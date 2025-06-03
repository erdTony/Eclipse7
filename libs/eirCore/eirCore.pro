QT -= gui
TEMPLATE = lib
DEFINES += EIRCORE_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    VersionInfo.cpp \
    eirCore.cpp

HEADERS += \
    Types.h \
    VersionInfo.h \
    eirCore_global.h \
    eirCore.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
