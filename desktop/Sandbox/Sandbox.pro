QT += core
QT += gui
QT += widgets
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../desktop.pri)
include(../../useBase.pri)
include(../../useType.pri)
include(../../useMatgeo.pri)
include(../../useCore.pri)
include(../../useExe.pri)
include(../../useWidgets.pri)
include(../../useColor.pri)
include(../../useImage.pri)

SOURCES += \
    SandboxApplication.cpp \
    SandboxData.cpp \
    SandboxEngine.cpp \
    SandboxMainWindow.cpp \
    SandboxView.cpp \
    main.cpp \

HEADERS += \
    SandboxApplication.h \
    SandboxData.h \
    SandboxEngine.h \
    SandboxMainWindow.h \
    SandboxView.h \
    version.h

FORMS += \
#    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ozSandbox.qrc

DISTFILES += \
    MM512A.jpg
