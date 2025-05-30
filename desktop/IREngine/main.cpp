#include "IfSearchApplication.h"
#include "IfSearchWindow.h"

#include "VersionInfo.h"
#include "version.h"

int main(int argc, char *argv[])
{
    VersionInfo vi(VER_MAJOR, VER_MINOR, VER_BRANCH, VER_RELEASE,
                   VER_STRING, VER_COPYRIGHT, VER_ORGNAME, VER_APPNAME);
    IfSearchApplication app(argc, argv, vi);
    IfSearchWindow window(&app);
    app.start();
    return app.exec();
}
