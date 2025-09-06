QT += core 
QT += gui
QT += widgets
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
include(../desktop.pri)
include(../../useBase.pri)
include(../../useType.pri)
include(../../useCore.pri)
include(../../useMatgeo.pri)
include(../../useNetwork.pri)
include(../../useWidgets.pri)
include(../../useExe.pri)

SOURCES += \
    EFPApplication.cpp \
    EFPFramesPage.cpp \
    EFPMainWindow.cpp \
    EFPSplashPage.cpp \
    main.cpp

HEADERS += \
    EFPApplication.h \
    EFPFramesPage.h \
    EFPMainWindow.h \
    EFPSplashPage.h

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
