QT *= gui
TEMPLATE = lib
DEFINES += EIRMATGEO_LIBRARY
CONFIG += c++23
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include (../libs.pri)
include (../../useBase.pri)
include (../../useMatgeo.pri)

SOURCES += \
    Binary.cpp \
    ByteHistogram.cpp \
    Iota.cpp \
    Point.cpp \
    Rational.cpp \
    RationalList.cpp \
    SCLine.cpp \
    SCRect.cpp \
    Size.cpp \
    eirMatgeo.cpp

HEADERS += \
    Binary.h \
    BinaryModifierMatrix.h \
    ByteHistogram.h \
    Iota.h \
    MatrixT.h \
    Point.h \
    Rational.h \
    RationalList.h \
    SCLine.h \
    SCRect.h \
    Size.h \
    eirMatgeo.h \
    eirMatgeo_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
