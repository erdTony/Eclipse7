# file: {Eclipse7 repo}/OpenCV4.pri

windows:{
INCLUDEPATH *= \code\3rdParty\OpenCV4\include
LIBS *= -L/code/3rdParty/OpenCV4/x64/mingw/lib
LIBS *= -lopencv_core4100
LIBS *= -lopencv_imgproc4100
LIBS *= -lopencv_objdetect4100
#LIBS *= /code/3rdParty/OpenCV4/x64/mingw/lib/libopencv_core4100.dll.a
#LIBS *= /code/3rdParty/OpenCV4/x64/mingw/lib/libopencv_imgproc4100.dll.a
#LIBS *= /code/3rdParty/OpenCV4/x64/mingw/lib/libopencv_objdetect4100.dll.a
}

linux:{
INCLUDEPATH *= /data/code/3rdParty/opencv4/include/opencv4
LIBS *= -L/data/code/3rdParty/opencv4/libs
LIBS *= /data/code/3rdParty/opencv4/lib/libopencv_core.so.4.12.0
LIBS *= /data/code/3rdParty/opencv4/lib/libopencv_imgproc.so.4.12.0
LIBS *= /data/code/3rdParty/opencv4/lib/libopencv_objdetect.so.4.12.0
#LIBS *= -lopencv_core
#LIBS *= -lopencv_highgui
#LIBS *= -lopencv_imageproc
#LIBS *= -lopencv_objdetect
DISTFILES *= /data/code/3rdParty/opencv4/lib/libopencv_core.so.4.12.0
DISTFILES *= /data/code/3rdParty/opencv4/lib/libopencv_imgproc.so.4.12.0
DISTFILES *= /data/code/3rdParty/opencv4/lib/libopencv_objdetect.so.4.12.0
}
