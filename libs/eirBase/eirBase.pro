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
    Bytes.cpp \
    CText.cpp \
    CTextList.cpp \
    EightCC.cpp \
    FSText.cpp \
    FSTextList.cpp \
    FourCC.cpp \
    MillisecondTime.cpp \
    NibbleArray.cpp \
    TriBool.cpp \
    UText.cpp \
    Uid.cpp \
    XText.cpp \
    eirBase.cpp

HEADERS += \
    AText.h \
    ATextList.h \
    Bytes.h \
    CText.h \
    CTextList.h \
    DataProperty.h \
    DualMap.h \
    EightCC.h \
    Enumeration.h \
    FSText.h \
    FSTextList.h \
    FourCC.h \
    MillisecondTime.h \
    NibbleArray.h \
    TriBool.h \
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
