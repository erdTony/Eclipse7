# {ottoZcode}/src/useCore.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirCore # ../../libs/eirCore ../eirCore
windows:LIBS *= -leirCore7
linux:LIBS *= -leirCore
LIBS *= -L$$DESTDIR
#message(--------/src/useCore.pri LIBS=$$LIBS DESTDIR==$$DESTDIR LIBDIR==$$LIBDIR INCLUDEPATH==$$INCLUDEPATH )

HEADERS +=


