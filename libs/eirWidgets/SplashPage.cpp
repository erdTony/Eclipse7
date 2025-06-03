#include "SplashPage.h"


SplashPage::SplashPage(const QString name, MainWindowPageStack *pMWS)
    : BaseMainWindowPage(name, pMWS)
{
    setObjectName("SplashPage:" + name);
}
