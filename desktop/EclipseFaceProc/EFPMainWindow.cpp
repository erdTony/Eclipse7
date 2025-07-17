#include "EFPMainWindow.h"

#include <QApplication>
#include <QEvent>
#include <QKeyEvent>
#include <QTimer>

#include "EFPFramesPage.h"
#include "EFPSplashPage.h"


EFPMainWindow::EFPMainWindow(BaseWidgetApplication *bwa)
    : MainWindowPageStack(bwa)
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("EFPMainWindow:" + QApplication::applicationName());
    QTimer::singleShot(250, this, &EFPMainWindow::setup);
}

EFPMainWindow::~EFPMainWindow() {}

void EFPMainWindow::setup()
{
    qDebug() << Q_FUNC_INFO;
    MainWindowPageStack::setup();
    mpSplashPage = new EFPSplashPage(this);
    Q_CHECK_PTR(mpSplashPage);
    mpSplashPage->setup();
    add(mpSplashPage);
    mpFramesPage = new EFPFramesPage(this);
    Q_CHECK_PTR(mpFramesPage);
    mpFramesPage->setup();
    add(mpFramesPage);
    show();
    Q_ASSERT(connect(this, &EFPMainWindow::keyEsc,
                     this, &EFPMainWindow::handleEsc));
    Q_ASSERT(connect(this, &EFPMainWindow::keyF1,
                     this, &EFPMainWindow::handleF1));
    qDebug() << Q_FUNC_INFO << "exit";
}

bool EFPMainWindow::event(QEvent *pEvent)
{
    Q_CHECK_PTR(pEvent);
    if (pEvent->type() == QEvent::KeyRelease)
        return handleKeyEvent(pEvent);
    else
        return QWidget::event(pEvent);
}

void EFPMainWindow::handleEsc()
{
    qInfo() << Q_FUNC_INFO;
    select(mpSplashPage);
}

void EFPMainWindow::handleF1()
{
    qInfo() << Q_FUNC_INFO;
    select(mpFramesPage);
}

bool EFPMainWindow::handleKeyEvent(QEvent *pEvent)
{
    QKeyEvent * pKeyEvent = (QKeyEvent *)pEvent;
    const int cKey = pKeyEvent->key();
    qInfo() << Q_FUNC_INFO << cKey;
    if (Qt::Key_Escape == cKey)
    {
        emit keyEsc();
        return true;
    }
    else if (Qt::Key_F1 == cKey)
    {
        emit keyF1();
        return true;
    }
    return false;
}
