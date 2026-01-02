# BuildDirEnum.pro - Build DirEnum and its libraries

TEMPLATE = subdirs

SUBDIRS +=              \
        eirCore		\
        eirExe          \
        eirNetwork      \
        eirGui		\
        eirStore        \
        eirMatgeo       \
        eirType         \
        eirWidgets	\
        DirEnum         \

eirCore.subdir      = libs/eirCore
eirExe.subdir       = libs/eirExe
eirNetwork.subdir   = libs/eirNetwork
eirGui.subdir       = libs/eirGui
eirStore.subdir     = libs/eirStore
eirMatgeo.subdir    = libs/eirMatgeo
eirType.subdir      = libs/eirType
eirWidgets.subdir   = libs/eirWidgets
DirEnum.subdir      = desktop/DirEnum

eirCore.depends     =
eirExe.depends      = eirCore eirType eirMatgeo
eirNetwork.depends  = eirCore eirType
eirGui.depends      = eirCore
eirStore.depends    = eirCore eirType eirNetwork
eirMatgeo.depends   = eirCore
eirType.depends     = eirCore
eirWidgets.depends  = eirCore eirMatgeo eirExe
Sandbox.depends     = eirCore eirNetwork eirStore
