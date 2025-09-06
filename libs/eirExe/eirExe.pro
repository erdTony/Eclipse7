QT *= core
QT *= gui
QT *= widgets
TEMPLATE = lib
DEFINES += EIREXE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../../useBase.pri)
include(../../useType.pri)
include(../../useMatgeo.pri)
include(../../useCore.pri)

SOURCES += \
    ActionManager.cpp \
    BaseWidgetApplication.cpp \
    CommandLine.cpp \
    ExeSupport.cpp \
    MainMenu.cpp \
    MainToolBar.cpp \
    Options.cpp \
    Random.cpp \
    Settings.cpp \
    eirExe.cpp

HEADERS += \
    ActionManager.h \
    BaseWidgetApplication.h \
    CommandLine.h \
    ExeSupport.h \
    MainMenu.h \
    MainToolBar.h \
    Options.h \
    Random.h \
    Settings.h \
    eirExe.h \
    eirExe_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
