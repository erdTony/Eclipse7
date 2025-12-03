#include <MainWindowPageStack.h>
#include "EfpApplication.h"

#include <QString>
#include <QTimer>

#include <AppHelper.h>
#include <Options.h>
#include <Url.h>
#include <VersionInfo.h>
#include "../../version.h"
#include "version.h"

#include "EfpMainWindow.h"

#define OPT app.wap()->opts()

int main(int argc, char *argv[])
{
    const VersionInfo cVI(VER_MAJOR, VER_MINOR, VER_RELEASE,
                          VER_BRANCH, VER_BUILD, VER_BRANCHNAME,
                          EIRVER_APPNAME, EIRVER_ORGNAME,
                          EIRVER_PRODDESC);
    EfpApplication app(argc, argv);
    cVI.updateApp(&app);
    OPT->set(cVI);
    OPT->addOrgAppOptions();
    OPT->addShowOptions();
    OPT->addHelpVerOptions();
    OPT->addPositional("inputUrl", "URL Location of Input Images");
    OPT->process();
    QString tUrlString("files://../EFPin");
    if ( ! OPT->isPositionalNull("inputUrl"))
        tUrlString = OPT->positional("inputUrl");
    Url tUrl(tUrlString);
    app.inputUrl(tUrl);
    return app.exec();
}

