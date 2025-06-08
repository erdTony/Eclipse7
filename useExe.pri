# {ottoZcode}/src/useExe.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirExe
windows:LIBS *= -leirExe7
linux:LIBS *= -leirExe
LIBS *= -L$$DESTDIR
message(--------/src/useExe.pri LIBS=$$LIBS DESTDIR==$$DESTDIR LIBDIR==$$LIBDIR INCLUDEPATH==$$INCLUDEPATH )


