QT += widgets
TEMPLATE = lib
DEFINES += EIRWIDGETS_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)
include (../../useBase.pri)
include (../../useCore.pri)

SOURCES += \
    BaseMainWindowPage.cpp \
    BaseWidgetApplication.cpp \
    Label.cpp \
    MainWindowPageStack.cpp \
    SplashPage.cpp \
    eirwidgets.cpp

HEADERS += \
    BaseMainWindowPage.h \
    BaseWidgetApplication.h \
    Label.h \
    MainWindowPageStack.h \
    SplashPage.h \
    eirWidgets_global.h \
    eirwidgets.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
