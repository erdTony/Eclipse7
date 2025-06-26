#include "SandboxMainWindow.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGridLayout>
#include <QIcon>
#include <QLabel>
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

    setupActions();

    scene()->set(SandboxScene::BackColor, Qt::green);
    scene()->setup();
    setMinimumSize(scene()->viewRect().size());
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
