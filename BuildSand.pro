# BuildSand.pro - Build IREngine and its libraries

TEMPLATE = subdirs

SUBDIRS +=          \
	eirBase			\
	eirColor		\
	eirCore			\
    eirExe \
	eirFacebase		\
	eirFacerec		\
    eirFaceres \
    eirGraphics \
	eirGui			\
	eirImage		\
    eirLogger \
    eirLogmgr \
    eirMatgeo \
    eirNetwork \
	eirObjdet		\
	eirQtCV			\
    eirQtVlan \
    eirRemote \
    eirState \
	eirStore		\
    eirSvg \
    eirType \
	eirWidgets		\
    eirVideo \
	eirXml  		\
    Sandbox        \

eirBase.subdir      = libs/eirBase
eirExe.subdir      = libs/eirExe
eirFaceres.subdir      = libs/eirFaceres
eirGraphics.subdir      = libs/eirGraphics
eirLogger.subdir      = libs/eirLogger
eirLogmgr.subdir      = libs/eirLogmgr
eirMatgeo.subdir      = libs/eirMatgeo
eirNetwork.subdir      = libs/eirNetwork
eirQtVlan.subdir      = libs/eirQtVlan
eirRemote.subdir      = libs/eirRemote
eirState.subdir      = libs/eirState
eirSvg.subdir      = libs/eirSvg
eirType.subdir      = libs/eirType
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
Sandbox.subdir     = desktop/Sandbox

eirBase.depends     =
eirExe.depends     = eirBase
eirFaceres.depends     = eirBase
eirGraphics.depends     = eirBase
eirLogger.depends     = eirBase
eirLogmgr.depends     = eirBase
eirMatgeo.depends     = eirBase
eirNetwork.depends     = eirBase
eirQtVlan.depends     = eirBase
eirRemote.depends     = eirBase
eirState.depends     = eirBase
eirSvg.depends     = eirBase
eirType.depends     = eirBase
eirVideo.depends     = eirBase
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
Sandbox.depends    = eirBase


