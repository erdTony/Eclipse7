# BuildSand.pro - Build IREngine and its libraries

TEMPLATE = subdirs

SUBDIRS +=          \
	eirBase			\
	eirColor		\
	eirCore			\
    eirExe \
    eirGraphics \
	eirGui			\
	eirImage		\
    eirMatgeo \
    eirType \
	eirWidgets		\
    Sandbox        \

eirBase.subdir      = libs/eirBase
eirColor.subdir     = libs/eirColor
eirCore.subdir      = libs/eirCore
eirExe.subdir      = libs/eirExe
eirGraphics.subdir      = libs/eirGraphics
eirGui.subdir       = libs/eirGui
eirImage.subdir     = libs/eirImage
eirMatgeo.subdir      = libs/eirMatgeo
eirType.subdir      = libs/eirType
eirWidgets.subdir   = libs/eirWidgets
Sandbox.subdir     = desktop/Sandbox

eirBase.depends     =
eirColor.depends    = eirBase
eirCore.depends     = eirBase
eirExe.depends     = eirBase
eirGraphics.depends     = eirBase
eirGui.depends      = eirBase
eirMatgeo.depends     = eirBase
eirType.depends     = eirBase
eirWidgets.depends  = eirBase
Sandbox.depends    = eirBase eirColor eirImage eirMatGeo eirWidgets


