# BuildIRE.pro - Build IREngine and its libraries

TEMPLATE = subdirs

SUBDIRS +=              \
        eirBase		\
        eirColor	\
        eirCore		\
        eirExe          \
#        eirFacebase     \
#        eirFacerec      \
#        eirFaceres      \
#        3     \
#        eirGui          \
#        eirImage        \
#        eirLogger       \
        eirMatgeo       \
        eirNetwork      \
#        eirObjdet	\
#        eirQtCV         \
#        eirQtVlan       \
#        eirRemote       \
#        eirState        \
        eirStore	\
#        eirSvg          \
        eirType         \
#        eirVideo        \
        eirWidgets	\
#        eirXml  	\
        EclipseFaceProc \


eirBase.subdir          = libs/eirBase
eirColor.subdir         = libs/eirColor
eirCore.subdir          = libs/eirCore
eirExe.subdir           = libs/eirExe
#eirGraphics.subdir      = libs/eirGraphics
#eirImage.subdir         = libs/eirImage
eirMatgeo.subdir        = libs/eirMatgeo
eirNetwork.subdir       = libs/eirNetwork
eirStore.subdir         = libs/eirStore
eirType.subdir          = libs/eirType
eirWidgets.subdir       = libs/eirWidgets
EclipseFaceProc.subdir  = desktop/EclipseFaceProc

#eirFacebase.subdir      = libs/eirFacebase
#eirFacerec.subdir       = libs/eirFacerec
#eirFaceres.subdir       = libs/eirFaceres
#eirGui.subdir           = libs/eirGui
#eirLogger.subdir        = libs/eirLogger
#eirObjdet.subdir        = libs/eirObjdet
#eirQtCV.subdir          = libs/eirQtCV
#eirQtVlan.subdir        = libs/eirQtVlan
#eirRemote.subdir        = libs/eirRemote
#eirState.subdir         = libs/eirState
#eirSvg.subdir           = libs/eirSvg
#eirVideo.subdir         = libs/eirVideo
#eirXml.subdir           = libs/eirXml

eirBase.depends         =
eirType.depends         = eirBase
eirMatgeo.depends       = eirBase eirType
eirColor.depends        = eirBase eirMatgeo
#eirImage.depends        = eirBase eirMatgeo eirColor
#eirGraphics.depends     = eirBase eirType eirMatgeo eirImage
eirCore.depends         = eirBase eirType
eirExe.depends          = eirBase eirType eirMatgeo eirCore
eirWidgets.depends      = eirBase eirType eirMatgeo eirCore eirExe #eirImage
eirNetwork.depends      = eirBase eirType
eirStore.depends        = eirBase eirType eirNetwork
#eirObjdet.depends       = eirBase eirType eirMatgeo eirCore
EclipseFaceProc.depends = eirBase eirType eirMatgeo eirCore \
                eirNetwork eirWidgets eirExe

#eirLogger.depends       = eirBase
#eirGui.depends          = eirBase
#eirState.depends        = eirBase
#eirQtCV.depends         = eirBase
#eirQtVlan.depends       = eirBase
#eirVideo.depends        = eirBase
#eirXml.depends          = eirBase
#eirSvg.depends          = eirBase
#eirFacerec.depends      = eirBase
#eirFaceres.depends      = eirBase
#eirFacebase.depends     = eirBase
#eirRemote.depends       = eirBase


