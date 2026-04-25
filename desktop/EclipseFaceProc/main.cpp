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

#define DOCTEST_CONFIG_IMPLEMENT
#include "../../doctest/doctest/doctest.h"

#define OPT app.wap()->opts()



int main(int argc, char *argv[])
{
    const VersionInfo cVI(VER_MAJOR, VER_MINOR, VER_RELEASE,
                          VER_BRANCH, VER_BUILD, VER_BRANCHNAME,
                          EIRVER_APPNAME, EIRVER_ORGNAME,
                          EIRVER_PRODDESC);

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    int res = context.run();
    if (context.shouldExit()) return res;

    EfpApplication app(argc, argv);
    cVI.updateApp(&app);
//    OPT->set(cVI);
  //  OPT->addOrgAppOptions();
    //OPT->addShowOptions();
//    OPT->addHelpVerOptions();
    //OPT->process();
    return app.exec();
}

