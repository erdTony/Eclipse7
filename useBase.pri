# {ottoZcode}/src/useBase.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirBase # ../../libs/eirWidget ../eirWidget
windows:LIBS *= -leirBase7
linux:LIBS *= -leirBase
LIBS *= -L$$DESTDIR
message(--------/src/useBase.pri LIBS=$$LIBS DESTDIR==$$DESTDIR LIBDIR==$$LIBDIR INCLUDEPATH==$$INCLUDEPATH )

HEADERS +=


