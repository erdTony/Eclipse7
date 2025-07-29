# {ottoZcode}/src/useStore.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirStore
windows:LIBS *= -leirStore7
linux:LIBS *= -leirStore
LIBS *= -L$$DESTDIR
message(--------/src/useStore.pri LIBS=$$LIBS DESTDIR==$$DESTDIR LIBDIR==$$LIBDIR INCLUDEPATH==$$INCLUDEPATH )

HEADERS +=


