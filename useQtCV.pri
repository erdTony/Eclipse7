# {ottoZcode}/src/useQtCV.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirQtCV # ../../libs/eirWidget ../eirWidget
windows:LIBS *= -leirQtCV7
linux:LIBS *= -leirQtCV
LIBS *= -L$$DESTDIR
message(--------/src/useQtCV.pri LIBS=$$LIBS DESTDIR==$$DESTDIR LIBDIR==$$LIBDIR INCLUDEPATH==$$INCLUDEPATH )
CVMAJOR = "CV4"

HEADERS +=


