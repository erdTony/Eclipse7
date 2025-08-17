QT -= gui
QT *= network
TEMPLATE = lib
DEFINES += EIRLOGGER_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../../useBase.pri) # ONLY!

CPPFLAGS *= -E -Dm

SOURCES += \
    AbstractLogOutput.cpp \
    BaseLogFilter.cpp \
    BaseLogFilterItem.cpp \
    BaseLogFormat.cpp \
    LogCondition.cpp \
    LogEntry.cpp \
    LogFileInfo.cpp \
    LogFuncInfo.cpp \
    LogItem.cpp \
    LogLevel.cpp \
    LogMessage.cpp \
    LogObject.cpp \
    LogOutText.cpp \
    eirLogger.cpp

HEADERS += \
    AbstractLogOutput.h \
    BaseLogFilter.h \
    BaseLogFilterItem.h \
    BaseLogFormat.h \
    Log.h \
    LogCondition.h \
    LogEntry.h \
    LogFileInfo.h \
    LogFuncInfo.h \
    LogItem.h \
    LogLevel.h \
    LogMacros.h \
    LogMessage.h \
    LogObject.h \
    LogOutText.h \
    eirLogger.h \
    eirLogger_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
