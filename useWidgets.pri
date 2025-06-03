# {ottoZcode}/src/useWidgets.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirWidgets # ../../libs/eirWidget ../eirWidget
windows:LIBS *= -leirWidgets7
linux:LIBS *= -leirWidgets
LIBS *= -L$$DESTDIR
message(--------/src/useWidgets.pri LIBS=$$LIBS DESTDIR==$$DESTDIR LIBDIR==$$LIBDIR INCLUDEPATH==$$INCLUDEPATH )

HEADERS +=


