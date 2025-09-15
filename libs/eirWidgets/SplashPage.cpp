#include "SplashPage.h"


SplashPage::SplashPage(const QString name)
    : BaseMainWindowPage(name)
{
    setObjectName("SplashPage:" + name);
}
