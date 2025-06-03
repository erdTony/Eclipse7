#include "BaseMainWindowPage.h"

#include "MainWindowPageStack.h"

BaseMainWindowPage::BaseMainWindowPage(const QString &n, MainWindowPageStack *pMWPS)
    : QWidget(pMWPS)
    , mpStack(pMWPS)
{
    setObjectName("SplashPage:" + n);
    q_check_ptr(pMWPS);
    connect(this, &BaseMainWindowPage::nameChanged,
            this, &BaseMainWindowPage::nameChange);
    name(n);
}

void BaseMainWindowPage::name(const QString n)
{
    mName = n;
    emit nameChanged(mName);
}

void BaseMainWindowPage::layout(QLayout *pLayout)
{
    mpLayout = pLayout;
    QWidget::setLayout(mpLayout);
    emit layoutSet(mpLayout);
}

void BaseMainWindowPage::nameChange(const QString &n)
{

}
