QT += core
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
    FilesImageAcqSource.cpp \
    ImageAcqConfig.cpp \
    ImageAcqManager.cpp \
    eirstore.cpp

HEADERS += \
    BaseImageAcqSource.h \
    FilesImageAcqSource.h \
    ImageAcqConfig.h \
    ImageAcqManager.h \
    eirStore_global.h \
    eirstore.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
