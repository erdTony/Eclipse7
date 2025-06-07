#include "BaseMainWindowPage.h"

#include "MainWindowPageStack.h"

BaseMainWindowPage::BaseMainWindowPage(const QString &n, MainWindowPageStack *pMWPS)
    : QWidget(pMWPS)
    , mpPageStack(pMWPS)
{
    setObjectName("SplashPage:" + n);
    q_check_ptr(pMWPS);
    name(n);
}

void BaseMainWindowPage::name(const QString n)
{
    mName = n;
    emit nameChanged(mName);
}


