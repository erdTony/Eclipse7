QT -= gui
TEMPLATE = lib
DEFINES += EIRTYPE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri))
include(../../useBase.pri)

SOURCES += \
    Ident.cpp \
    IdentMap.cpp \
    Key.cpp \
    KeySeg.cpp \
    KeySegList.cpp \
    MillisecondTime.cpp \
    NibbleArray.cpp \
    Null.cpp \
    ObjectHelper.cpp \
    TriBool.cpp \
    Uid.cpp \
    eirType.cpp

HEADERS += \
    Ident.h \
    IdentMap.h \
    Key.h \
    KeyMap.h \
    KeySeg.h \
    KeySegList.h \
    List.h \
    MillisecondTime.h \
    NibbleArray.h \
    Null.h \
    ObjectHelper.h \
    Queue.h \
    TriBool.h \
    Uid.h \
    eirType.h \
    eirType_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
