QT += core 
QT += gui
QT += widgets
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
include(../desktop.pri)
include(../../useBase.pri)
include(../../useLogger.pri)
include(../../useType.pri)
include(../../useMatgeo.pri)
include(../../useCore.pri)
include(../../useNetwork.pri)
include(../../useColor.pri)
include(../../useStore.pri)
include(../../useGui.pri)
include(../../useImage.pri)
include(../../useWidgets.pri)
include(../../useObjdet.pri)
include(../../useExe.pri)

SOURCES += \
    EfpApplication.cpp \
    EfpFramesPage.cpp \
    EfpImageReader.cpp \
    EfpMainWindow.cpp \
    EfpSplashPage.cpp \
    main.cpp

HEADERS += \
    EfpApplication.h \
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

win32: LIBS += -L$$PWD/../../../../3rdParty/OpenCV4/x64/mingw/lib/ -llibopencv_objdetect4100.dll
INCLUDEPATH += $$PWD/../../../../3rdParty/OpenCV4/include/opencv2/objdetect
DEPENDPATH += $$PWD/../../../../3rdParty/OpenCV4/include/opencv2/objdetect
