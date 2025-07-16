QT += widgets
TEMPLATE = lib
DEFINES += EIRWIDGETS_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)
include (../../useBase.pri)
include (../../useType.pri)
include (../../useMatgeo.pri)
include (../../useCore.pri)
include (../../useExe.pri)

SOURCES += \
    BaseMainWindowPage.cpp \
    BaseWidgetApplication.cpp \
    Gallery.cpp \
    GalleryCell.cpp \
    GalleryGrid.cpp \
    GalleryProperties.cpp \
    GalleryUid.cpp \
    Label.cpp \
    MainWindowPageStack.cpp \
    SplashPage.cpp \
    eirWidgets.cpp

HEADERS += \
    BaseMainWindowPage.h \
    BaseWidgetApplication.h \
    Gallery.h \
    GalleryCell.h \
    GalleryGrid.h \
    GalleryProperties.h \
    GalleryUid.h \
    Label.h \
    MainWindowPageStack.h \
    SplashPage.h \
    eirWidgets.h \
    eirWidgets_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
