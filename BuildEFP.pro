# BuildIRE.pro - Build IREngine and its libraries

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
    eirVideo \
    eirWidgets		\
	eirXml  		\
    EclipseFaceProc        \

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
eirState.subdir     = libs/eirState
eirStore.subdir     = libs/eirStore
eirSvg.subdir     = libs/eirSvg
eirType.subdir     = libs/eirType
eirVideo.subdir   = libs/eirVideo
eirWidgets.subdir   = libs/eirWidgets
eirXml.subdir       = libs/eirXml
EclipseFaceProc.subdir     = desktop/EclipseFaceProc

eirBase.depends     =
eirLogger.depends     = eirBase
eirType.depends    = eirBase
eirMatgeo.depends     = eirBase
eirCore.depends     = eirBase
eirGui.depends      = eirBase
eirWidgets.depends    = eirBase
eirState.depends    = eirBase
eirExe.depends     = eirBase    eirCore
eirLogmgr.depends     = eirBase

eirColor.depends    = eirBase
eirImage.depends    = eirBase
eirQtCV.depends     = eirBase
eirObjdet.depends   = eirBase
eirQtVlan.depends     = eirBase
eirVideo.depends    = eirBase

eirGraphics.depends     = eirBase
eirNetwork.depends     = eirBase
eirXml.depends    = eirBase
eirStore.depends    = eirBase
eirSvg.depends    = eirBase
eirFacerec.depends  = eirBase
eirFaceres.depends     = eirBase
eirFacebase.depends = eirBase
eirRemote.depends     = eirBase
EclipseFaceProc.depends    = eirBase eirType eirCore eirWidgets


