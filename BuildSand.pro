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
eirExe.subdir       = libs/eirExe
eirGraphics.subdir  = libs/eirGraphics
eirGui.subdir       = libs/eirGui
eirImage.subdir     = libs/eirImage
eirMatgeo.subdir    = libs/eirMatgeo
eirType.subdir      = libs/eirType
eirWidgets.subdir   = libs/eirWidgets
Sandbox.subdir      = desktop/Sandbox

eirBase.depends     =
eirColor.depends    = eirBase eirMatgeo
eirCore.depends     = eirBase
eirExe.depends      = eirBase eirType eirCore
eirGraphics.depends = eirBase
eirGui.depends      = eirBase
eirImage.depends    = eirBase eirMatgeo eirColor
eirMatgeo.depends   = eirBase
eirType.depends     = eirBase
eirWidgets.depends  = eirBase
Sandbox.depends     = eirBase eirType eirMatgeo eirCore \
                        eirExe eirWidgets eirColor  eirImage


