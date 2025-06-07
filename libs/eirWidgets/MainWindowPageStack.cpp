#include "MainWindowPageStack.h"

#include <QStackedLayout>
#include <QWidget>

#include "BaseMainWindowPage.h"
#include "BaseWidgetApplication.h"

MainWindowPageStack::MainWindowPageStack(BaseWidgetApplication *pBWA)
    : QMainWindow{}
    , mpApp(pBWA)
    , mpStackLayout(new QStackedLayout())
    , mpMainGrid(new QGridLayout())
    , mpTabWidget(new QTabWidget())
    , mpStackWidget(new QWidget())
{
    setObjectName("MainWindowPageStack:" + app()->applicationName());
    stackLayout()->setObjectName("QStackedWidget:" + app()->applicationName());
}

void MainWindowPageStack::setup()
{
    qDebug() << Q_FUNC_INFO;
    tabs()->setTabPosition(QTabWidget::West);
    setCentralWidget(tabs());
    qDebug() << Q_FUNC_INFO << "exit";
}

Index MainWindowPageStack::nameIndex(BaseMainWindowPage *pBMWP) const
{
    q_check_ptr(pBMWP);
    return nameIndex(pBMWP->name());
}

Index MainWindowPageStack::nameIndex(const QString n) const
{
    Index result = -1;
    const Index k = mPageList.count();
    for (Index ix = 0; ix < k; ++ix)
        if (mPageList.at(ix)->name() == n) { result = ix; break; }
    return result;
}

bool MainWindowPageStack::isValidIndex(const Index ix)
{
    return mPageList.count() == tabs()->count()
           && ix >= 0 && ix < mPageList.count();
}

Index MainWindowPageStack::add(BaseMainWindowPage *pBMWP)
{
    q_check_ptr(pBMWP);
    Index result = -1;
    //(void)remove(pBMWP);
    result = tabs()->addTab(pBMWP, pBMWP->name());
    qDebug() << Q_FUNC_INFO << result;
    return result;
}

bool MainWindowPageStack::remove(BaseMainWindowPage *pBMWP)
{
    q_check_ptr(pBMWP);
    return remove(nameIndex(pBMWP));
}

bool MainWindowPageStack::remove(const Index ix)
{
    if ( ! isValidIndex(ix)) return false;
    BaseMainWindowPage * pPage = mPageList.at(ix);
    stackLayout()->removeWidget(pPage);
    tabs()->removeTab(ix);
    pPage->deleteLater();
    return true;
}

