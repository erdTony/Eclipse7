#include <MainWindowPageStack.h>
#include "EFPApplication.h"

#include <QString>
#include <QTimer>

#include <ExeSupport.h>
#include <Options.h>
#include <Url.h>
#include <VersionInfo.h>
#include "../../version.h"
#include "version.h"

#include "EFPMainWindow.h"

#define OPT app.exe().opts()

int main(int argc, char *argv[])
{
    const VersionInfo cVI(VER_MAJOR, VER_MINOR, VER_RELEASE,
                          VER_BRANCH, VER_BUILD, VER_BRANCHNAME,
                          EIRVER_APPNAME, EIRVER_ORGNAME, EIRVER_PRODDESC);
    EFPApplication app(argc, argv);
    EFPMainWindow w;
    app.exe().main(&w);
    cVI.updateApp(&app);
    OPT->set(cVI);
    OPT->addOrgAppOptions();
    OPT->addShowOptions();
    OPT->addHelpVerOptions();
    OPT->addPositional("inputUrl", "URL Location of Input Images");
    OPT->process();
    app.set(Url(OPT->containsPositional("inputUrl")
                ? OPT->positional("inputUrl")
                : QString("files:///../EFPin")));
    return app.exec();
}
