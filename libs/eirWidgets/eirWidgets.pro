QT += widgets
TEMPLATE = lib
DEFINES += EIRWIDGETS_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)
include (../../useCore.pri)
include (../../useMatgeo.pri)

SOURCES += \
    BaseMainWindowPage.cpp \
    BinarySpinBox.cpp \
    Label.cpp \
    LabelMap.cpp \
    LineEdit.cpp \
    LineEditMap.cpp \
    MsecSpinBox.cpp \
    SplashPage.cpp \
    eirWidgets.cpp

HEADERS += \
    BaseMainWindowPage.h \
    BinarySpinBox.h \
    Label.h \
    LabelMap.h \
    LineEdit.h \
    LineEditMap.h \
    MsecSpinBox.h \
    SplashPage.h \
    eirWidgets.h \
    eirWidgets_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
