# {Eclipse7}/useLog.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirLog
windows:LIBS *= -leirLog7
linux:LIBS *= -leirLog
LIBS *= -L$$DESTDIR
#message(--------/src/useLog.pri LIBS=$$LIBS DESTDIR==$$DESTDIR INCLUDEPATH==$$INCLUDEPATH )


