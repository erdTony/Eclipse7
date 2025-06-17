QT -= gui
TEMPLATE = lib
DEFINES += EIRBASE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)

SOURCES += \
    AText.cpp \
    ATextList.cpp \
    FileInfo.cpp \
    FileName.cpp \
    FilePath.cpp \
    FunctionInfo.cpp \
    FunctionName.cpp \
    TimeString.cpp \
    UText.cpp \
    Uid.cpp \
    eirbase.cpp

HEADERS += \
    AText.h \
    ATextList.h \
    FileInfo.h \
    FileName.h \
    FilePath.h \
    FunctionInfo.h \
    FunctionName.h \
    TimeString.h \
    Types.h \
    UText.h \
    Uid.h \
    eirBase_global.h \
    eirbase.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
