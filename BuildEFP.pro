# BuildEFP.pro - Build Eclipse Face Processor and its libraries

TEMPLATE = subdirs

SUBDIRS +=              \
#        eirColor	\
        eirCore		\
        eirExe          \
#        eirFacebase     \
#        eirFacerec      \
#        eirFaceres      \
        eirGraphics     \
        eirGui          \
#        eirImage        \
        eirMatgeo       \
        eirNetwork      \
        eirObjdet	\
        eirQtCV         \
#        eirQtVlan       \
#        eirRemote       \
#        eirState        \
        eirStore	\
#        eirSvg          \
#        eirVideo        \
        eirWidgets	\
#        eirXml  	\
        EclipseFaceProc \


#eirColor.subdir         = libs/eirColor
eirCore.subdir          = libs/eirCore
eirExe.subdir           = libs/eirExe
eirGraphics.subdir      = libs/eirGraphics
eirGui.subdir           = libs/eirGui
#eirImage.subdir         = libs/eirImage
eirMatgeo.subdir        = libs/eirMatgeo
eirNetwork.subdir       = libs/eirNetwork
eirObjdet.subdir        = libs/eirObjdet
eirQtCV.subdir          = libs/eirQtCV
eirStore.subdir         = libs/eirStore
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

eirCore.depends
eirMatgeo.depends       =
eirNetwork.depends      =
#eirColor.depends        = eirMatgeo
eirQtCV.depends         = eirCore
eirObjdet.depends       = eirCore eirQtCV
eirStore.depends        = eirNetwork
eirGui.depends          = eirCore eirMatgeo
eirGraphics.depends     = eirCore eirMatgeo
#eirImage.depends        = eirCore eirMatgeo eirColor eirGraphics
#eirFacebase.depends     = eirCore eirImage
eirWidgets.depends      = eirCore eirMatgeo
eirObjdet.depends       = eirCore eirMatgeo
eirExe.depends          = eirCore eirMatgeo eirWidgets
##eirStore.depends        = eirBase eirType eirNetwork
##eirGui.depends          = eirBase eirType eirMatgeo eirCore
##eirGraphics.depends     = eirBase eirType eirMatgeo eirCore
##eirImage.depends        = eirBase eirLogger eirType eirMatgeo eirColor eirGraphics
##eirFacebase.depends     = eirBase eirLogger eirImage
##eirExe.depends          = eirBase eirType eirMatgeo eirCore eirWidgets
EclipseFaceProc.depends =  eirCore  eirMatgeo   \
                          eirNetwork  eirStore eirGui  \
                          eirWidgets  eirQtCV eirObjdet

#eirGraphics.depends     = eirBase eirType eirMatgeo eirImage
#eirState.depends        = eirBase
#eirQtVlan.depends       = eirBase
#eirVideo.depends        = eirBase
#eirXml.depends          = eirBase
#eirSvg.depends          = eirBase
#eirFacerec.depends      = eirBase
#eirFaceres.depends      = eirBase
#eirRemote.depends       = eirBase


