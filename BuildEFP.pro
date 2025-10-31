# BuildEFP.pro - Build Eclipse Face Processor and its libraries

TEMPLATE = subdirs

SUBDIRS +=              \
        eirBase		\
        eirColor	\
        eirCore		\
        eirExe          \
#        eirFacebase     \
#        eirFacerec      \
#        eirFaceres      \
        eirGraphics     \
        eirGui          \
        eirImage        \
        eirLogger       \
        eirMatgeo       \
        eirNetwork      \
##        eirObjdet	\
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
eirGraphics.subdir      = libs/eirGraphics
eirGui.subdir           = libs/eirGui
eirImage.subdir         = libs/eirImage
eirLogger.subdir        = libs/eirLogger
eirMatgeo.subdir        = libs/eirMatgeo
eirNetwork.subdir       = libs/eirNetwork
##eirObjdet.subdir        = libs/eirObjdet
eirStore.subdir         = libs/eirStore
eirType.subdir          = libs/eirType
eirWidgets.subdir       = libs/eirWidgets
EclipseFaceProc.subdir  = desktop/EclipseFaceProc

#eirFacebase.subdir      = libs/eirFacebase
#eirFacerec.subdir       = libs/eirFacerec
#eirFaceres.subdir       = libs/eirFaceres
#eirGraphics.subdir      = libs/eirGraphics
#eirQtCV.subdir          = libs/eirQtCV
#eirQtVlan.subdir        = libs/eirQtVlan
#eirRemote.subdir        = libs/eirRemote
#eirState.subdir         = libs/eirState
#eirSvg.subdir           = libs/eirSvg
#eirVideo.subdir         = libs/eirVideo
#eirXml.subdir           = libs/eirXml

eirBase.depends         =
eirLogger.depends       = eirBase
eirType.depends         = eirBase
eirMatgeo.depends       = eirBase eirType
eirCore.depends         = eirBase eirType
eirNetwork.depends      = eirBase eirType
eirColor.depends        = eirBase eirMatgeo
##eirObjdet.depends       = eirBase eirMatgeo
eirStore.depends        = eirBase eirType eirNetwork
eirGui.depends          = eirBase eirType eirMatgeo eirCore
eirGraphics.depends     = eirBase eirType eirMatgeo eirCore
eirImage.depends        = eirBase eirLogger eirType eirMatgeo eirColor eirGraphics
eirWidgets.depends      = eirBase eirType eirMatgeo eirCore
eirObjdet.depends       = eirBase eirType eirMatgeo eirCore
eirExe.depends          = eirBase eirType eirMatgeo eirCore eirWidgets
EclipseFaceProc.depends = eirBase eirLogger eirType eirMatgeo eirCore  \
                          eirNetwork eirColor eirStore eirGui eirImage \
                          eirWidgets eirExe
##                          eirWidgets eirObjdet eirExe

#eirGraphics.depends     = eirBase eirType eirMatgeo eirImage
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


