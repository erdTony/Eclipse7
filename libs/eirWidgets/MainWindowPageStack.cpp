#include "MainWindowPageStack.h"

#include <QStackedLayout>
#include <QWidget>

#include <BaseWidgetApplication.h>

#include "BaseMainWindowPage.h"

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
    qInfo() << Q_FUNC_INFO;
    tabs()->setTabPosition(QTabWidget::West);
    setCentralWidget(tabs());
    qDebug() << Q_FUNC_INFO << "exit";
}

void MainWindowPageStack::select(BaseMainWindowPage *pBMWP)
{
    qInfo() << Q_FUNC_INFO << pBMWP->name();
    mpStackLayout->setCurrentWidget(pBMWP);
    update();
}

void MainWindowPageStack::updateSizes(const Size minSize, const Size maxSize)
{
    if ( ! minSize.isEmpty())
        minimumSize() |= minSize;
    if ( ! maxSize.isEmpty())
        maximumSize() &= maxSize;
    qInfo() << Q_FUNC_INFO << minSize << maxSize
            << minimumSize() << maximumSize();
}

Index MainWindowPageStack::nameIndex(BaseMainWindowPage *pBMWP) const
{
    Q_CHECK_PTR(pBMWP);
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
    Q_CHECK_PTR(pBMWP);
    Index result = -1;
    stackLayout()->addWidget(pBMWP);
    result = tabs()->addTab(pBMWP, pBMWP->name());
    pBMWP->pageIndex(result);
    updateSizes(pBMWP->minimumSize(), pBMWP->maximumSize());
    qDebug() << Q_FUNC_INFO << result;
    return result;
}

bool MainWindowPageStack::remove(BaseMainWindowPage *pBMWP)
{
    Q_CHECK_PTR(pBMWP);
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

