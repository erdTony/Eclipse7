QT *= core
QT *= gui
QT *= widgets
TEMPLATE = lib
DEFINES += EIREXE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../../useCore.pri)
include(../../useMatgeo.pri)
include(../../useGui.pri)
include(../../useWidgets.pri)

SOURCES += \
    ActionManager.cpp \
    AppHelper.cpp \
    CommandLine.cpp \
    MainMenu.cpp \
    MainWindowPageStack.cpp \
    MenuItem.cpp \
    Options.cpp \
    Random.cpp \
    Settings.cpp \
    eirExe.cpp

HEADERS += \
    ActionManager.h \
    AppHelper.h \
    CommandLine.h \
    MainMenu.h \
    MainWindowPageStack.h \
    MenuItem.h \
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

DISTFILES += \
    ../../useGui.pri
