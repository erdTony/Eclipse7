QT -= gui
TEMPLATE = lib
DEFINES += EIRCORE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)
include (../../useBase.pri)
include (../../useType.pri)

SOURCES += \
    ObjectHelper.cpp \
    VersionInfo.cpp \
    eirCore.cpp

HEADERS += \
    ObjectHelper.h \
    VersionInfo.h \
    eirCore_global.h \
    eirCore.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
