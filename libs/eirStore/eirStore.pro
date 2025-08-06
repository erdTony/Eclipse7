QT += core
QT += statemachine
TEMPLATE = lib
DEFINES += EIRSTORE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../../useBase.pri)
include(../../useType.pri)
include(../../useNetwork.pri)

SOURCES += \
    BaseImageAcqSource.cpp \
    DirInfo.cpp \
    FileData.cpp \
    FileInfo.cpp \
    FileSysInfo.cpp \
    FilesImageAcqSource.cpp \
    ImageAcq.cpp \
    ImageAcqConfig.cpp \
    ImageAcqMachine.cpp \
    ImageAcqManager.cpp \
    ImageAcqProperties.cpp \
    ImageAcqThread.cpp \
    eirStore.cpp

HEADERS += \
    BaseImageAcqSource.h \
    DirInfo.h \
    FileData.h \
    FileInfo.h \
    FileSysInfo.h \
    FilesImageAcqSource.h \
    ImageAcq.h \
    ImageAcqConfig.h \
    ImageAcqMachine.h \
    ImageAcqManager.h \
    ImageAcqProperties.h \
    ImageAcqThread.h \
    eirStore.h \
    eirStore_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
