QT -= gui
TEMPLATE = lib
DEFINES += EIRTYPE_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri))

SOURCES += \
    AText.cpp \
    Key.cpp \
    KeySeg.cpp \
    KeySegList.cpp \
    UText.cpp \
    eirtype.cpp

HEADERS += \
    AText.h \
    Key.h \
    KeyMap.h \
    KeySeg.h \
    KeySegList.h \
    UText.h \
    eirType_global.h \
    eirtype.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
