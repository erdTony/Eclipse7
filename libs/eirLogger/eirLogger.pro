QT -= gui
TEMPLATE = lib
DEFINES += EIRLOGGER_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../../useBase.pri) # ONLY!

SOURCES += \
    LogCategory.cpp \
    LogItem.cpp \
    eirlogger.cpp

HEADERS += \
    LogCategory.h \
    LogItem.h \
    eirLogger_global.h \
    eirlogger.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
