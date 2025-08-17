#include "EFPApplication.h"

#include <ExeSupport.h>
#include <KeySeg.h>

EFPApplication::EFPApplication(int &argc, char **argv)
    : BaseWidgetApplication{argc, argv}
{
    qInfo() << Q_FUNC_INFO;
    setObjectName("EFPApplication:" + applicationName());
}

void EFPApplication::setup()
{
    qInfo() << Q_FUNC_INFO;
    exe()->addShowOptions();
    exe()->addHelpVerOptions();
    exe()->addPositional("inputUrl",
              "Location specification of Input Images");

    exe()->execute();

    if (exe()->contains("inputUrl"))
        mInputUrl.set(exe()->positional("inputUrl"));
    else
        mInputUrl = "files:///../EFPin";

}

void EFPApplication::start()
{

}
