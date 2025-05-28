# BuildIRE.pro - Build IREngine and its libraries

TEMPLATE = subdirs

SUBDIRS +=          \
	eirBase			\
	eirColor		\
	eirCore			\
	eirFacebase		\
	eirFacerec		\
	eirGui			\
	eirImage		\
	eirObjdet		\
	eirQtCV			\
	eirStore		\
	eirWidgets		\
	eirXml  		\
    IREngine        \

eirBase.subdir      = libs/eirBase
eirColor.subdir     = libs/eirColor
eirCore.subdir      = libs/eirCore
eirFacebase.subdir  = libs/eirFacebase
eirFacerec.subdir   = libs/eirFacerec
eirGui.subdir       = libs/eirGui
eirImage.subdir     = libs/eirImage
eirObjdet.subdir    = libs/eirObjdet
eirQtCV.subdir      = libs/eirQtCV
eirStore.subdir     = libs/eirStore
eirXml.subdir       = libs/eirXml
eirWidgets.subdir   = libs/eirWidgets
IREngine.subdir     = desktop/IREngine

eirBase.depends     =
eirCore.depends     = eirBase
eirGui.depends      = eirBase
eirWidgets.depends  = eirBase
eirXml.depends      = eirBase
eirFacebase.depends = eirBase
eirColor.depends    = eirBase
eirFacerec.depends  = eirBase
eirImage.depends    = eirBase
eirObjdet.depends   = eirBase
eirQtCV.depends     = eirBase
eirStore.depends    = eirBase
IREngine.depends    = eirBase


