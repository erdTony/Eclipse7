QT += core
QT += statemachine
TEMPLATE = lib
DEFINES += EIRSTORE_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../libs.pri)
include(../../useCore.pri)

SOURCES += \
    AbstractBlobBase.cpp \
    BaseImageAcqSource.cpp \
    BlobBaseFile.cpp \
    BlobBasePgSql.cpp \
    BlobBaseSqlLite.cpp \
    BlobItem.cpp \
    BlobStore.cpp \
    BlobStoreUrl.cpp \
    DirInfo.cpp \
    FileData.cpp \
    FileInfo.cpp \
    FileSysInfo.cpp \
    FilesAcqSource.cpp \
    ImageAcq.cpp \
    ImageAcqConfig.cpp \
    ImageAcqMachine.cpp \
    ImageAcqManager.cpp \
    ImageAcqProperties.cpp \
    ImageAcqThread.cpp \
    eirStore.cpp

HEADERS += \
    AbstractBlobBase.h \
    BaseImageAcqSource.h \
    BlobBaseFile.h \
    BlobBasePgSql.h \
    BlobBaseSqlLite.h \
    BlobItem.h \
    BlobStore.h \
    BlobStoreUrl.h \
    DirInfo.h \
    FileData.h \
    FileInfo.h \
    FileSysInfo.h \
    FilesAcqSource.h \
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
