# {ottoZcode}/src/useNetwork.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirNetwork
windows:LIBS *= -leirNetwork7
linux:LIBS *= -leirNetwork
LIBS *= -L$$DESTDIR
message(--------/src/useNetwork.pri LIBS=$$LIBS DESTDIR==$$DESTDIR LIBDIR==$$LIBDIR INCLUDEPATH==$$INCLUDEPATH )

HEADERS +=


