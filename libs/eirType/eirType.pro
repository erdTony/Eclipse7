QT -= gui
TEMPLATE = lib
DEFINES += EIRTYPE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri))
include(../../useBase.pri)

SOURCES += \
    Id.cpp \
    IdMap.cpp \
    Key.cpp \
    KeySeg.cpp \
    KeySegList.cpp \
    KeyValueMap.cpp \
    Null.cpp \
    ObjectHelper.cpp \
    UidKeyMap.cpp \
    Value.cpp \
    eirType.cpp

HEADERS += \
    DualMap.h \
    Id.h \
    IdMap.h \
    Key.h \
    KeyMap.h \
    KeySeg.h \
    KeySegList.h \
    KeyValueMap.h \
    Null.h \
    ObjectHelper.h \
    Queue.h \
    UidKeyMap.h \
    Value.h \
    eirType.h \
    eirType_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
