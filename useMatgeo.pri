# {Eclipse7}/useMatgeo.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirMatgeo
windows:LIBS *= -leirMatgeo7
linux:LIBS *= -leirMatgeo
LIBS *= -L$$DESTDIR
message(--------/src/useMatgeo.pri LIBS=$$LIBS DESTDIR==$$DESTDIR INCLUDEPATH==$$INCLUDEPATH )


