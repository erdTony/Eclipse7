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
    BinarySpinBox.cpp \
    Gallery.cpp \
    GalleryCell.cpp \
    GalleryGrid.cpp \
    GalleryProperties.cpp \
    GalleryUid.cpp \
    Label.cpp \
    LabelMap.cpp \
    LineEdit.cpp \
    LineEditMap.cpp \
    MainWindowPageStack.cpp \
    MsecSpinBox.cpp \
    SplashPage.cpp \
    eirWidgets.cpp

HEADERS += \
    BaseMainWindowPage.h \
    BaseWidgetApplication.h \
    BinarySpinBox.h \
    Gallery.h \
    GalleryCell.h \
    GalleryGrid.h \
    GalleryProperties.h \
    GalleryUid.h \
    Label.h \
    LabelMap.h \
    LineEdit.h \
    LineEditMap.h \
    MainWindowPageStack.h \
    MsecSpinBox.h \
    SplashPage.h \
    eirWidgets.h \
    eirWidgets_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
