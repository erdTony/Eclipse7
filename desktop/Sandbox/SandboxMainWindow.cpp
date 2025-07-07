#include "SandboxMainWindow.h"

#include <QApplication>
#include <QDateTime>
#include <QGraphicsView>
#include <QGridLayout>
#include <QIcon>
#include <QLabel>
#include <QProgressBar>
#include <QStatusBar>
#include <QStyle>
#include <QToolBar>
#include <QTimer>
#include <QWidget>

#include <ActionManager.h>
#include <KeySeg.h>

#include "SandboxApplication.h"
#include "SandboxEngine.h"
#include "SandboxScene.h"

SandboxMainWindow::SandboxMainWindow(SandboxApplication *parent)
    : mpApplication(parent)
    , mpActions(new ActionManager(this))
{
    qInfo() << Q_FUNC_INFO;
    setObjectName("SandboxMainWindow:" + app()->applicationName());
}

SandboxMainWindow::~SandboxMainWindow()
{
    qInfo() << Q_FUNC_INFO;
    if (mpActions)   mpActions->deleteLater();
    if (mpScene)   mpScene->deleteLater();
}

void SandboxMainWindow::initialize()
{
    qInfo() << Q_FUNC_INFO;
    mpActions = new ActionManager(this);

    mpScene = new SandboxScene(this);
    scene()->initialize();
    emit initialized();
}

void SandboxMainWindow::configure()
{
    qInfo() << Q_FUNC_INFO;
    // TODO QSettings from SandboxData
    scene()->configure();
    emit configured();
}


void SandboxMainWindow::setup()
{
    qInfo() << Q_FUNC_INFO;

    mpMainToolBar = QMainWindow::addToolBar("Main");
    Q_CHECK_PTR(mpMainToolBar);
    setupActions();

    mpProgressBar = new QProgressBar(this);
    Q_CHECK_PTR(mpProgressBar);
    mpProgressBar->setMaximumWidth(100);
    mpProgressBar->setMaximum(101);
    mpProgressBar->setMinimum(0);

    mpStatusBar = QMainWindow::statusBar();
    Q_CHECK_PTR(mpStatusBar);
    mpStatusBar->setSizeGripEnabled(false);
    mpStatusBar->addPermanentWidget(mpProgressBar);
    mpStatusBar->setMinimumHeight(mpProgressBar->height());

    scene()->set(SandboxScene::BackColor, Qt::green);
    scene()->setup();
    setMinimumSize(scene()->viewRect().size().expanded(Size(8)));
    setCentralWidget(scene()->widget());
    update();

    show();
    emit setuped();
}


void SandboxMainWindow::start()
{
    qInfo() << Q_FUNC_INFO;
    scene()->start();
    emit started();
}

void SandboxMainWindow::flip()
{
    ++mFlipCount;
    mPassCount = 0;
}

void SandboxMainWindow::pass(const Count swaps)
{
    const qreal cPixelCount = scene()->viewRect().area();
    const unsigned cPercent = qRound(100.0 * qreal(swaps) / cPixelCount);
    QString msg = QString("%1 Pass: %2 + %3 Swap: %4")
                      .arg(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"))
                      .arg(mFlipCount, 6)
                      .arg(++mPassCount, -6)
                      .arg(swaps, 6);
    mpStatusBar->showMessage(msg);
    mpProgressBar->setValue(cPercent);
}

QAction *SandboxMainWindow::action(const Key &key)
{
    return actions()->action(key);
}

void SandboxMainWindow::setupActions()
{
    qInfo() << Q_FUNC_INFO;
    ActionManager::Action actQuit = actions()->add("Main/Quit");
    toolBar()->addAction(actQuit);

}

QIcon SandboxMainWindow::styleIcon(const KeySeg &key) const
{
    QIcon result;
    QStyle * pStyle = QApplication::style();
    if ("Splash" == key)
        result = pStyle->standardIcon(QStyle::SP_DesktopIcon);
    else if ("Gallery" == key)
        result = pStyle->standardIcon(QStyle::SP_DirOpenIcon);
    else if ("Log" == key)
        result = pStyle->standardIcon(QStyle::SP_FileIcon);
    else if ("Quit" == key)
        result = pStyle->standardIcon(QStyle::SP_ArrowRight);
    return result;
}
