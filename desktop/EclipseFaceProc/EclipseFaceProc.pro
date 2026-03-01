QT += core 
QT += gui
QT += widgets
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
include(../desktop.pri)
include(../../useCore.pri)
include(../../useExe.pri)
include(../../useGui.pri)
include(../../useImage.pri)
include(../../useObjdet.pri)
include(../../useStore.pri)
include(../../useWidgets.pri)

SOURCES += \
    EfpApplication.cpp \
    EfpFrameProcessor.cpp \
    EfpFramesPage.cpp \
    EfpImageReader.cpp \
    EfpMainWindow.cpp \
    EfpSplashPage.cpp \
    main.cpp

HEADERS += \
    EfpApplication.h \
    EfpFrameProcessor.h \
    EfpFramesPage.h \
    EfpImageReader.h \
    EfpMainWindow.h \
    EfpSplashPage.h \
    version.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    EclipseFaceProc.qrc


