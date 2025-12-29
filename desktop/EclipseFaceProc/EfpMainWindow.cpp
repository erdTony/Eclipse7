#include "EfpMainWindow.h"

#include <QApplication>
#include <QEvent>
#include <QKeyEvent>
#include <QTimer>

#include "EfpApplication.h"
#include "EfpFramesPage.h"
#include "EfpSplashPage.h"


EfpMainWindow::EfpMainWindow()
    : MainWindowPageStack()
    , mpSplashPage(new EfpSplashPage(this))
    , mpFramesPage(new EfpFramesPage(this))
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("EFPMainWindow:" + QApplication::applicationName());
    QTimer::singleShot(250, this, &EfpMainWindow::setup);
}

EfpMainWindow::~EfpMainWindow() {;}

void EfpMainWindow::initialize()
{
    qDebug() << Q_FUNC_INFO;

    Q_CHECK_PTR(mpSplashPage);
    Q_CHECK_PTR(mpFramesPage);

    Q_ASSERT(connect(this, &EfpMainWindow::keyEsc,
                     this, &EfpMainWindow::handleEsc));
    Q_ASSERT(connect(this, &EfpMainWindow::keyF1,
                     this, &EfpMainWindow::handleF1));

    emit initialized();
}

void EfpMainWindow::setup()
{
    qDebug() << Q_FUNC_INFO;
    MainWindowPageStack::setup();
    setWindowTitle("EclipseIR Face Processor");
    mpSplashPage->setup();
    add(mpSplashPage);
    mpFramesPage->setup();
    add(mpFramesPage);
    show();
    qDebug() << Q_FUNC_INFO << "exit";
    emit setupd();
}

void EfpMainWindow::start()
{
    qDebug() << Q_FUNC_INFO;
    frames()->start(APP->inputDir());
    emit started();
}

bool EfpMainWindow::event(QEvent *pEvent)
{
    Q_CHECK_PTR(pEvent);
    if (pEvent->type() == QEvent::KeyRelease)
        return handleKeyEvent(pEvent);
    else
        return QWidget::event(pEvent);
}

void EfpMainWindow::handleEsc()
{
    qInfo() << Q_FUNC_INFO;
    select(mpSplashPage);
}

void EfpMainWindow::handleF1()
{
    qInfo() << Q_FUNC_INFO;
    select(mpFramesPage);
}

bool EfpMainWindow::handleKeyEvent(QEvent *pEvent)
{
    qDebug() << Q_FUNC_INFO;
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
