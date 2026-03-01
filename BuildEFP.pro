# BuildEFP.pro - Build Eclipse Face Processor and its libraries

TEMPLATE = subdirs

SUBDIRS +=              \
        eirCore		\
        eirExe          \
        eirGui          \
        eirImage        \
        eirObjdet	\
        eirStore	\
        eirVideo        \
        eirWidgets	\
        EclipseFaceProc \


eirCore.subdir          = libs/eirCore
eirExe.subdir           = libs/eirExe
eirGraphics.subdir      = libs/eirGraphics
eirGui.subdir           = libs/eirGui
eirImage.subdir         = libs/eirImage
eirVideo.subdir         = libs/eirVideo
eirObjdet.subdir        = libs/eirObjdet
eirStore.subdir         = libs/eirStore
eirWidgets.subdir       = libs/eirWidgets
EclipseFaceProc.subdir  = desktop/EclipseFaceProc

eirCore.depends         =
eirGui.depends          = eirCore
eirWidgets.depends      = eirCore
eirGui.depends          = eirCore
eirImage.depends        = eirCore eirWidgets
eirVideo.depends        = eirCore eirImage
eirObjdet.depends       = eirCore eirImage
eirStore.depends        = eirCore eirImage
eirExe.depends          = eirCore eirWidgets
EclipseFaceProc.depends = eirCore eirStore eirGui eirWidgets  eirObjdet




