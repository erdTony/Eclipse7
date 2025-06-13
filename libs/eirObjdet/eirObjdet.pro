QT += gui
QT += xml
TEMPLATE = lib
DEFINES += EIROBJDET_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)
include (../../OpenCV4.pri)
include (../../useBase.pri)
include (../../useType.pri)
include (../../useMatgeo.pri)
include (../../useCore.pri)

SOURCES += \
    DetectorResult.cpp \
    DetectorResultList.cpp \
    Objdet.cpp \
    ObjdetCatalog.cpp \
    ObjdetCatalogItem.cpp \
    ObjdetEyes.cpp \
    ObjdetFrontal.cpp \
    ObjdetParameters.cpp \
    ObjdetParametersEyes.cpp \
    ObjdetParametersFrontal.cpp \
    ObjdetRawArguments.cpp \
    ObjdetResource.cpp \
    ObjdetResult.cpp \
    ObjdetResultMap.cpp \
    eirobjdet.cpp

HEADERS += \
    DetectorResult.h \
    DetectorResultList.h \
    Objdet.h \
    ObjdetCatalog.h \
    ObjdetCatalogItem.h \
    ObjdetEyes.h \
    ObjdetFrontal.h \
    ObjdetParameters.h \
    ObjdetParametersEyes.h \
    ObjdetParametersFrontal.h \
    ObjdetRawArguments.h \
    ObjdetResource.h \
    ObjdetResult.h \
    ObjdetResultMap.h \
    eirObjdet_global.h \
    eirobjdet.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
