QT -= gui
TEMPLATE = lib
DEFINES += EIREXE_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../../useType.pri)

SOURCES += \
    ApplicationHelper.cpp \
    CommandLine.cpp \
    Options.cpp \
    Settings.cpp \
    eirexe.cpp

HEADERS += \
    ApplicationHelper.h \
    CommandLine.h \
    Options.h \
    Settings.h \
    eirExe_global.h \
    eirexe.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
