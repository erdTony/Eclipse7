QT  += core
QT  += gui
QT  += widgets
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../Desktop.pri)
include(../../useBase.pri)
include(../../useType.pri)
include(../../useNetwork.pri)

SOURCES += \
    DirEnumProperties.cpp \
    EnumWindow.cpp \
    FileEnumerator.cpp \
    PropertyEditor.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    DirEnumProperties.h \
    EnumWindow.h \
    FileEnumerator.h \
    MainWindow.h \
    PropertyEditor.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
