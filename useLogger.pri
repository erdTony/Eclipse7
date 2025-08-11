# {Eclipse7}/useLogger.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirLogger
windows:LIBS *= -leirLogger7
linux:LIBS *= -leirLogger
LIBS *= -L$$DESTDIR
message(--------/src/useLogger.pri LIBS=$$LIBS DESTDIR==$$DESTDIR INCLUDEPATH==$$INCLUDEPATH )


