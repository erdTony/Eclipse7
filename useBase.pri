# {Eclipse7}/useBase.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirBase
windows:LIBS *= -leirBase7
linux:LIBS *= -leirBase
LIBS *= -L$$DESTDIR
message(--------/src/useBase.pri LIBS=$$LIBS DESTDIR==$$DESTDIR INCLUDEPATH==$$INCLUDEPATH )


