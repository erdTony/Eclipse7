QT -= gui
TEMPLATE = lib
DEFINES += EIRTYPE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri))
include(../../useBase.pri)

SOURCES += \
    FileInfo.cpp \
    Iota.cpp \
    Key.cpp \
    KeySeg.cpp \
    KeySegList.cpp \
    eirtype.cpp

HEADERS += \
    FileInfo.h \
    Iota.h \
    Key.h \
    KeyMap.h \
    KeySeg.h \
    KeySegList.h \
    eirType_global.h \
    eirtype.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
