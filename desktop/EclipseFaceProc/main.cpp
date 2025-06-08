#include <MainWindowPageStack.h>
#include "EFPApplication.h"

#include <QTimer>

#include <VersionInfo.h>
#include "../../version.h"

#include "EFPMainWindow.h"

int main(int argc, char *argv[])
{
    const VersionInfo cVI(VER_MAJOR, VER_MINOR, VER_RELEASE, VER_BRANCH,
                          VER_BUILD, VER_BRANCHNAME,
                          "Eclipse Face Processor",
                          EIRVER_ORGNAME, EIRVER_PRODUCT);
    EFPApplication a(argc, argv);
    EFPMainWindow w(&a);
    return a.exec();
}
