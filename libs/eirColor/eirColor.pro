QT += gui
TEMPLATE = lib
DEFINES += EIRCOLOR_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)

SOURCES += \
    AnyColor.cpp \
    AnyColorTable.cpp \
    BrightnessContrast.cpp \
    Color.cpp \
    ColorTable.cpp \
    Pixel32.cpp \
    RationalColorList.cpp \
    RgbColor.cpp \
    Rgba32Table.cpp \
    eircolor.cpp

HEADERS += \
    AnyColor.h \
    AnyColorTable.h \
    BrightnessContrast.h \
    Color.h \
    ColorTable.h \
    Pixel32.h \
    RationalColorList.h \
    RgbColor.h \
    Rgba32Table.h \
    eirColor_global.h \
    eircolor.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
