# {ottoZcode}/src/useObjdet.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirObjdet # ../../libs/eirWidget ../eirWidget
windows:LIBS *= -leirObjdet7
linux:LIBS *= -leirObjdet
LIBS *= -L$$DESTDIR
message(--------/src/useObjdet.pri LIBS=$$LIBS DESTDIR==$$DESTDIR LIBDIR==$$LIBDIR INCLUDEPATH==$$INCLUDEPATH )

HEADERS +=

unix:!macx: LIBS *= -L$$PWD/../../../../../../lib/x86_64-linux-gnu/ -lopencv_core -lopencv_objdetect
INCLUDEPATH *= $$PWD/../../../../../../usr/include/opencv4
DEPENDPATH *= $$PWD/../../../../../../usr/include/opencv4

