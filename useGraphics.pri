# {ottoZcode}/src/useGraphics.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirGraphics
windows:LIBS *= -leirGraphics7
linux:LIBS *= -leirGraphics
LIBS *= -L$$DESTDIR
message(--------/src/useGraphics.pri LIBS=$$LIBS DESTDIR==$$DESTDIR LIBDIR==$$LIBDIR INCLUDEPATH==$$INCLUDEPATH )



