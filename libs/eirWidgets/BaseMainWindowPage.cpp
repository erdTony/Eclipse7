#include "BaseMainWindowPage.h"

#include <QSizePolicy>

#include "MainWindowPageStack.h"

BaseMainWindowPage::BaseMainWindowPage(const QString &n,
                            MainWindowPageStack *pMWPS)
    : QWidget(pMWPS)
    , mpPageStack(pMWPS)
{
    setObjectName("SplashPage:" + n);
    Q_CHECK_PTR(pMWPS);
    name(n);
}

void BaseMainWindowPage::name(const QString n)
{
    mName = n;
    emit nameChanged(mName);
}

void BaseMainWindowPage::setSize(const QSizePolicy::Policy szp, const Size sz1, const Size sz2)
{
    if ((int)szp & QSizePolicy::GrowFlag)
    {
        setMinimumSize(sz1);
        pageStack()->updateSizes(sz1, Size());
        Q_UNUSED(sz2);
    }
    // TODO BaseMainWindowPage::setSize() other policies
}


