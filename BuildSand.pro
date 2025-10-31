# BuildSand.pro - Build IREngine and its libraries

TEMPLATE = subdirs

SUBDIRS +=              \
        eirBase		\
        eirLogger	\
        eirColor	\
        eirCore		\
        eirExe          \
        eirGraphics     \
        eirGui		\
        eirImage	\
        eirMatgeo       \
        eirType         \
        eirWidgets      \
        Sandbox         \

eirBase.subdir      = libs/eirBase
eirLogger.subdir    = libs/eirLogger
eirColor.subdir     = libs/eirColor
eirCore.subdir      = libs/eirCore
eirExe.subdir       = libs/eirExe
eirGraphics.subdir  = libs/eirGraphics
eirGui.subdir       = libs/eirGui
eirImage.subdir     = libs/eirImage
eirMatgeo.subdir    = libs/eirMatgeo
eirType.subdir      = libs/eirType
eirWidgets.subdir   = libs/eirWidgets

Sandbox.subdir      = desktop/Sandbox

eirBase.depends     =
eirLogger.depends   = eirBase
eirColor.depends    = eirBase eirMatgeo
eirCore.depends     = eirBase
eirWidgets.depends  = eirBase eirMatgeo eirCore # eirExe
eirExe.depends      = eirBase eirType eirMatgeo eirCore eirWidgets
eirGraphics.depends = eirBase
eirGui.depends      = eirBase
eirMatgeo.depends   = eirBase
eirType.depends     = eirBase
eirImage.depends    = eirBase eirLogger eirType eirMatgeo eirColor eirWidgets
Sandbox.depends     = eirBase eirLogger eirType eirMatgeo eirCore \
                        eirExe eirWidgets eirColor  eirImage


