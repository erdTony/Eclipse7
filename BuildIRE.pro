# BuildIRE.pro - Build IREngine and its libraries

TEMPLATE = subdirs

SUBDIRS +=          \
	eirColor		\
	eirCore			\
    eirExe \
	eirFacebase		\
	eirFacerec		\
    eirFaceres \
    eirGraphics \
	eirGui			\
	eirImage		\
    eirMatgeo \
    eirNetwork \
	eirObjdet		\
	eirQtCV			\
    eirQtVlan \
    eirRemote \
    eirState \
	eirStore		\
    eirSvg \
	eirWidgets		\
    eirVideo \
	eirXml  		\
    IREngine        \

eirExe.subdir      = libs/eirExe
eirFaceres.subdir      = libs/eirFaceres
eirGraphics.subdir      = libs/eirGraphics
eirMatgeo.subdir      = libs/eirMatgeo
eirNetwork.subdir      = libs/eirNetwork
eirQtVlan.subdir      = libs/eirQtVlan
eirRemote.subdir      = libs/eirRemote
eirState.subdir      = libs/eirState
eirSvg.subdir      = libs/eirSvg
eirVideo.subdir      = libs/eirVideo
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

eirCore.depends     =
eirExe.depends     = eirCore eirType eirMatgeo
eirFaceres.depends     = eirCore
eirGraphics.depends     = eirCore
eirMatgeo.depends     = eirCore
eirNetwork.depends     = eirCore
eirQtVlan.depends     = eirCore
eirRemote.depends     = eirCore
eirState.depends     = eirCore
eirSvg.depends     = eirCore
eirType.depends     = eirCore
eirVideo.depends     = eirCore
eirCore.depends     = eirCore
eirGui.depends      = eirCore
eirWidgets.depends  = eirCore eirMatgeo  eirExe
eirXml.depends      = eirCore
eirFacebase.depends = eirCore
eirColor.depends    = eirCore eirMatgeo
eirFacerec.depends  = eirCore
eirImage.depends    = eirCore  eirMatgeo eirColor
eirObjdet.depends   = eirCore
eirQtCV.depends     = eirCore
eirStore.depends    = eirCore
IREngine.depends    = eirCore  eirMatgeo  \
    eirExe eirWidgets eirColor  eirImage


