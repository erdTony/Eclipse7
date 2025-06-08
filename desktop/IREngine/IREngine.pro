QT       += core
QT       += gui
QT       += widgets
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../desktop.pri)
include(../../OpenCV4.pri)

SOURCES += \
    BaseObjdetEngine.cpp \
    BaseObjdetMarker.cpp \
    VersionInfo.cpp \
    main.cpp \
    EyesMarker.cpp  \
#    EyesObjdet.cpp  \
    FrontalMarker.cpp  \
    FrontalObjdet.cpp  \
    IfSearchApplication.cpp  \
    IfSearchEngine.cpp  \
    IfSearchEngine-Slots.cpp  \
    IfSearchEngine-Init.cpp  \
    IfSearchWindow.cpp  \
    MainWindow.cpp  \
    Objdet.cpp  \
    ObjdetCatalog.cpp  \
    ObjdetCatalogItem.cpp  \
    ObjdetFrontal.cpp  \
    ObjdetParameters.cpp  \
    ObjdetParametersEyes.cpp  \
    ObjdetParametersFrontal.cpp  \
    ObjdetRawArguments.cpp  \
    ObjdetResource.cpp  \
    ObjdetResult.cpp  \
    ObjdetResultMap.cpp  \
    ObjectHelper.cpp  \

HEADERS += \
    BaseObjdetEngine.h \
    BaseObjdetMarker.h \
    EyesMarker.h  \
#    EyesObjdet.h  \
    FrontalMarker.h  \
    FrontalObjdet.h  \
    IfSearchApplication.h  \
    IfSearchEngine.h  \
    IfSearchWindow.h  \
    MainWindow.h  \
    Objdet.h  \
    ObjdetCatalog.h  \
    ObjdetCatalogItem.h  \
    ObjdetFrontal.h  \
    ObjdetParameters.h  \
    ObjdetParametersEyes.h  \
    ObjdetParametersFrontal.h  \
    ObjdetRawArguments.h  \
    ObjdetResource.h  \
    ObjdetResult.h  \
    ObjdetResultMap.h  \
    ObjectHelper.h  \
    Property.h \
    VersionInfo.h \
    version.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    BINDIR.pri \
    BLDCFG.pri \
    CVMAJOR.pri \
    eIRonly24.ico
