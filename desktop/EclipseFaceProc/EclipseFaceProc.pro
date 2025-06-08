QT += core 
QT += gui
QT += widgets
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../desktop.pri)
include(../../useBase.pri)
include(../../useType.pri)
include(../../useCore.pri)
include(../../useMatgeo.pri)
include(../../useWidgets.pri)
include(../../useExe.pri)

SOURCES += \
    EFPApplication.cpp \
    EFPMainWindow.cpp \
    EFPSplash.cpp \
    main.cpp

HEADERS += \
    EFPApplication.h \
    EFPMainWindow.h \
    EFPSplash.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    EclipseFaceProc.qrc
