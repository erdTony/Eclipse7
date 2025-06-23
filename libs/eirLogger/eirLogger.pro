QT -= gui
QT *= network
TEMPLATE = lib
DEFINES += EIRLOGGER_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../../useBase.pri) # ONLY!

SOURCES += \
    BaseLogOutput.cpp \
    LogCategory.cpp \
    LogContext.cpp \
    LogItem.cpp \
    LogObject.cpp \
    Logger.cpp \
    QtLogFields.cpp \
    TextFileLogOutput.cpp \
    eirlogger.cpp

HEADERS += \
    BaseLogOutput.h \
    Log.h \
    LogCategory.h \
    LogContext.h \
    LogItem.h \
    LogMacros.h \
    LogObject.h \
    Logger.h \
    QtLogFields.h \
    TextFileLogOutput.h \
    eirLogger_global.h \
    eirlogger.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
