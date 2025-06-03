# file: {Eclipse7 repo}/OpenCV4.pri

INCLUDEPATH *= /data/code/3rdParty/opencv4/include/opencv4
LIBS *= -L/data/code/3rdParty/opencv4/libs

LIBS *= -lopencv_core
#LIBS *= -lopencv_highgui
LIBS *= -lopencv_imageproc
LIBS *= -lopencv_objdetect

DISTFILES *= /data/code/3rdParty/opencv4/libs/libopencv_core.so.4.12.0
DISTFILES *= /data/code/3rdParty/opencv4/libs/libopencv_imageproc.so.4.12.0
DISTFILES *= /data/code/3rdParty/opencv4/libs/libopencv_objdetect.so.4.12.0

