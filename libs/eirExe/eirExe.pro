QT *= core
QT *= gui
TEMPLATE = lib
DEFINES += EIREXE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../../useBase.pri)
include(../../useType.pri)
include(../../useCore.pri)

SOURCES += \
    ActionManager.cpp \
    CommandLine.cpp \
    ExeSupport.cpp \
    Options.cpp \
    Settings.cpp \
    eirExe.cpp

HEADERS += \
    ActionManager.h \
    CommandLine.h \
    ExeSupport.h \
    Options.h \
    Settings.h \
    eirExe.h \
    eirExe_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
