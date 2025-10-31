# {ozCode}/src/BINDIR.pri
windows:BINDIR  = "/home/code/bin"
linux:BINDIR    = "/home/code/bin"
#message(............/src/BINDIR.pri = $$BINDIR)

# for OpenGL on manzy ##251031aho Merry Halloween
linux:LIBS *=  -L/snap/gnome-42-2204/226/usr/lib/x86_64-linux-gnu


