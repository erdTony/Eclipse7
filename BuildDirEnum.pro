# BuildDirEnum.pro - Build DirEnum and its libraries

TEMPLATE = subdirs

SUBDIRS +=              \
        eirBase		\
        eirLogger	\
        eirCore		\
        eirExe          \
        eirNetwork      \
        eirGui		\
        eirStore        \
        eirMatgeo       \
        eirType         \
        eirWidgets	\
        DirEnum         \

eirBase.subdir      = libs/eirBase
eirLogger.subdir    = libs/eirLogger
eirCore.subdir      = libs/eirCore
eirExe.subdir       = libs/eirExe
eirNetwork.subdir   = libs/eirNetwork
eirGui.subdir       = libs/eirGui
eirStore.subdir     = libs/eirStore
eirMatgeo.subdir    = libs/eirMatgeo
eirType.subdir      = libs/eirType
eirWidgets.subdir   = libs/eirWidgets
DirEnum.subdir      = desktop/DirEnum

eirBase.depends     =
eirLogger.depends   = eirBase
eirCore.depends     = eirBase
eirExe.depends      = eirBase eirType eirMatgeo eirCore
eirNetwork.depends  = eirBase eirType
eirGui.depends      = eirBase
eirStore.depends    = eirBase eirType eirNetwork
eirMatgeo.depends   = eirBase
eirType.depends     = eirBase
eirWidgets.depends  = eirBase eirMatgeo eirCore eirExe
Sandbox.depends     = eirBase eirType eirNetwork eirStore
