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
    CTextList.cpp \
    FSText.cpp \
    FSTextList.cpp \
    UText.cpp \
    XText.cpp \
    eirBase.cpp

HEADERS += \
    AText.h \
    ATextList.h \
    CText.h \
    CTextList.h \
    DataProperty.h \
    DualMap.h \
    Enumeration.h \
    FSText.h \
    FSTextList.h \
    Types.h \
    UText.h \
    XText.h \
    eirBase.h \
    eirBase_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
