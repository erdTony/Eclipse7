# {Eclipse7}/useImage.pri
include(LIBDIR.pri)
include(DESTDIR.pri)

INCLUDEPATH *= $$LIBDIR/eirImage
windows:LIBS *= -leirImage7
linux:LIBS *= -leirImage
LIBS *= -L$$DESTDIR
#message(--------/src/useImage.pri LIBS=$$LIBS DESTDIR==$$DESTDIR INCLUDEPATH==$$INCLUDEPATH )


