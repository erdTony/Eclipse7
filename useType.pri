# {ottoZcode}/src/useType.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirType
windows:LIBS *= -leirType7
linux:LIBS *= -leirType
LIBS *= -L$$DESTDIR
message(--------/src/useType.pri LIBS=$$LIBS DESTDIR==$$DESTDIR LIBDIR==$$LIBDIR INCLUDEPATH==$$INCLUDEPATH )

HEADERS +=


