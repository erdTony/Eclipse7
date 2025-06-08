QT += core
QT += gui
QT += widgets
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../desktop.pri)

SOURCES += \
    SandboxApplication.cpp \
    SandboxData.cpp \
    SandboxEngine.cpp \
    SandboxMainWindow.cpp \
    SandboxScene.cpp \
    SandboxView.cpp \
    main.cpp \
#    mainwindow.cpp

HEADERS += \
    SandboxApplication.h \
    SandboxData.h \
    SandboxEngine.h \
    SandboxMainWindow.h \
    SandboxScene.h \
    SandboxView.h \
#    mainwindow.h \
    version.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ozSandbox.qrc

DISTFILES += \
    MM512A.jpg
