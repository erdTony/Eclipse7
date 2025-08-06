QT  += core
QT  += gui
QT  += widgets
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../Desktop.pri)
include(../../useBase.pri)
include(../../useType.pri)
include(../../useWidgets.pri)
include(../../useNetwork.pri)
include(../../useStore.pri)

SOURCES += \
    DirEnumProperties.cpp \
    EnumWindow.cpp \
    FileEnumParmWidget.cpp \
    FileEnumerator.cpp \
    FileEnumeratorParms.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    DirEnumProperties.h \
    EnumWindow.h \
    FileEnumParmWidget.h \
    FileEnumerator.h \
    FileEnumeratorParms.h \
    MainWindow.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
