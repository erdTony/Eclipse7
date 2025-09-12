#include "EFPApplication.h"


#include <ExeSupport.h>
#include <MainWindowPageStack.h>
#include <Options.h>
#include <KeySeg.h>

EFPApplication::EFPApplication(int &argc, char **argv)
    : BaseWidgetApplication{argc, argv}
    , mExeSupport(this)
{
    qInfo() << Q_FUNC_INFO;
    setObjectName("EFPApplication:" + applicationName());
}

void EFPApplication::setup()
{
    qInfo() << Q_FUNC_INFO;
//    Q_ASSERT(connect(stack(), &MainWindowPageStack::activated,
  //           this, &EFPApplication::resume));

}

void EFPApplication::start()
{

}

void EFPApplication::resume()
{
}
