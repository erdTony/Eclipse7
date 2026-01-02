# BuildSand.pro - Build IREngine and its libraries

TEMPLATE = subdirs

SUBDIRS +=              \
        eirColor	\
        eirCore		\
        eirExe          \
        eirGraphics     \
        eirGui		\
        eirImage	\
        eirMatgeo       \
        eirWidgets      \
        Sandbox         \

eirColor.subdir     = libs/eirColor
eirCore.subdir      = libs/eirCore
eirExe.subdir       = libs/eirExe
eirGraphics.subdir  = libs/eirGraphics
eirGui.subdir       = libs/eirGui
eirImage.subdir     = libs/eirImage
eirMatgeo.subdir    = libs/eirMatgeo
eirWidgets.subdir   = libs/eirWidgets

Sandbox.subdir      = desktop/Sandbox

eirCore.depends     =
eirLogger.depends   = eirCore
eirColor.depends    = eirCore eirMatgeo
eirWidgets.depends  = eirCore eirMatgeo  # eirExe
eirExe.depends      = eirCore  eirMatgeo  eirWidgets
eirGraphics.depends = eirCore
eirGui.depends      = eirCore
eirMatgeo.depends   = eirCore
eirType.depends     = eirCore
eirImage.depends    = eirCore   eirMatgeo eirColor eirWidgets
Sandbox.depends     = eirCore   eirMatgeo  \
                        eirExe eirWidgets eirColor  eirImage


