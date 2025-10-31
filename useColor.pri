# {Eclipse7}/useColor.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirColor
windows:LIBS *= -leirColor7
linux:LIBS *= -leirColor
LIBS *= -L$$DESTDIR
#message(--------/src/useColor.pri LIBS=$$LIBS DESTDIR==$$DESTDIR INCLUDEPATH==$$INCLUDEPATH )


