QT -= gui
QT *= network
QT *= statemachine
QT *= sql
QT *= xml
TEMPLATE = lib
DEFINES += EIRLOGGER_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../../useBase.pri) # ONLY!

CPPFLAGS *= -E -Dm

SOURCES += \
    BaseLogFilter.cpp \
    BaseLogFilterItem.cpp \
    LogCondition.cpp \
    LogEntry.cpp \
    LogFileInfo.cpp \
    LogFormat.cpp \
    LogFuncInfo.cpp \
    LogItem.cpp \
    LogLevel.cpp \
    LogMachine.cpp \
    LogMessage.cpp \
    LogObject.cpp \
    LogOutText.cpp \
    LogOutput.cpp \
    eirLogger.cpp

HEADERS += \
    BaseLogFilter.h \
    BaseLogFilterItem.h \
    Log.h \
    LogCondition.h \
    LogEntry.h \
    LogFileInfo.h \
    LogFormat.h \
    LogFuncInfo.h \
    LogItem.h \
    LogLevel.h \
    LogMachine.h \
    LogMacros.h \
    LogMessage.h \
    LogObject.h \
    LogOutText.h \
    LogOutput.h \
    eirLogger.h \
    eirLogger_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
