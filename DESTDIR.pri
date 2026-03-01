# {Eclipse6}/src/DESTDIR.pri
#message(========/src/DESTDIR.pri)

OURDEST = "{bindir}/{bldcfg}{osbits}-Qt{qtver}CV{cvver}-{ver}"
#message(OURDEST = $$OURDEST)
#message(VER_STRING = $$VER_STRING)

include(version.pri)
include(BINDIR.pri)
include(BLDCFG.pri)
include(OSBITS.pri)
include(CVVERSION.pri)

OURDEST = $$replace(OURDEST, "{bindir}", $$BINDIR)
OURDEST = $$replace(OURDEST, "{bldcfg}", $$BLDCFG)
OURDEST = $$replace(OURDEST, "{osbits}", $$OSBITS)
OURDEST = $$replace(OURDEST, "{qtver}", $$QT_VERSION)
OURDEST = $$replace(OURDEST, "{cvver}", $$CVVERSION)
OURDEST = $$replace(OURDEST, "{ver}", $$VER_STRING)
#message(OURDEST = $$OURDEST)

DESTDIR = $$OURDEST
#message(DESTDIR = $$DESTDIR)
