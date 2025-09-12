# {ottoZcode}/src/useGui.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirGui # ../../libs/eirGui ../eirGui
windows:LIBS *= -leirGui7
linux:LIBS *= -leirGui
LIBS *= -L$$DESTDIR
#message(--------/src/useGui.pri LIBS=$$LIBS DESTDIR==$$DESTDIR LIBDIR==$$LIBDIR INCLUDEPATH==$$INCLUDEPATH )

HEADERS +=


