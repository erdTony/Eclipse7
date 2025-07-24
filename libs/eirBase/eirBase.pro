QT += core
QT += gui
QT += network
TEMPLATE = lib
DEFINES += EIRBASE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)

SOURCES += \
    AText.cpp \
    ATextList.cpp \
    CText.cpp \
    Enumeration.cpp \
    Key.cpp \
    KeySeg.cpp \
    KeySegList.cpp \
    MillisecondTime.cpp \
    NibbleArray.cpp \
    ObjectHelper.cpp \
    UText.cpp \
    Uid.cpp \
    XText.cpp \
    eirBase.cpp

HEADERS += \
    AText.h \
    ATextList.h \
    CText.h \
    DataProperty.h \
    DualMap.h \
    Enumeration.h \
    Key.h \
    KeyMap.h \
    KeySeg.h \
    KeySegList.h \
    MillisecondTime.h \
    NibbleArray.h \
    ObjectHelper.h \
    Types.h \
    UText.h \
    Uid.h \
    XText.h \
    eirBase.h \
    eirBase_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
