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

SandboxMainWindow::SandboxMainWindow(SandboxApplication *parent)
    : mpApplication(parent)
    , mpActions(new ActionManager(this))
    , cmBaseSize(Size(512))
{
    qInfo() << Q_FUNC_INFO << baseSize();
    setObjectName("SandboxMainWindow:" + app()->applicationName());
}

SandboxMainWindow::~SandboxMainWindow()
{
    qInfo() << Q_FUNC_INFO;
    if (mpActions)   mpActions->deleteLater();
}

void SandboxMainWindow::initialize()
{
    qInfo() << Q_FUNC_INFO;
    mpActions = new ActionManager(this);
    emit initialized();
}

void SandboxMainWindow::configure()
{
    qInfo() << Q_FUNC_INFO;
    // TODO QSettings from SandboxData
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
    mpProgressBar->setMaximumWidth(200);
    mpProgressBar->setMaximum(101);
    mpProgressBar->setMinimum(0);

    mpStatusBar = QMainWindow::statusBar();
    Q_CHECK_PTR(mpStatusBar);
    mpStatusBar->setSizeGripEnabled(false);
    mpStatusBar->addPermanentWidget(mpProgressBar);
    mpStatusBar->setMinimumHeight(mpProgressBar->height());

    mpImageLabel = new QLabel(this);
    Q_CHECK_PTR(mpImageLabel);
    mpImageLabel->setMinimumSize(baseSize());
    setCentralWidget(mpImageLabel);
    emit setuped();
}


void SandboxMainWindow::start()
{
    qInfo() << Q_FUNC_INFO;
    QImage tSubjectImage(":/Monroe.jpg");
    set(tSubjectImage);
    show();
    emit started();
}

void SandboxMainWindow::set(const QImage &qi)
{
    qInfo() << Q_FUNC_INFO << qi;
    Q_CHECK_PTR(mpImageLabel);
    app()->engine()->subjectImage(qi);
    mPixmap = QPixmap::fromImage(app()->engine()->subjectImage());
    mpImageLabel->setPixmap(mPixmap);
    update();
    mFrameCount = 1;
    QTimer::singleShot(1000, app()->engine(), &SandboxEngine::start);
}

void SandboxMainWindow::showSwapping(const Count swapPass,
                                      const Count numSwaps,
                                      const QImage &qi)
{
//    qInfo() << Q_FUNC_INFO << swapPass << numSwaps << qi;
    const unsigned cPixelCount = baseSize().area();
    const unsigned cPercent = qRound(100.0 * qreal(numSwaps) / cPixelCount);
    mPixmap = QPixmap::fromImage(qi);
    mpImageLabel->setPixmap(mPixmap);
    update();
    QString msg = QString("%1 Pass: %2 + %3")
                      .arg(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"))
                      .arg(mFrameCount, 6)
                      .arg(swapPass, -6);
    mpStatusBar->showMessage(msg);
    mpProgressBar->setValue(cPercent);
}

void SandboxMainWindow::showFlipped(const QImage &qi)
{
    qInfo() << Q_FUNC_INFO << qi;
    mPixmap = QPixmap::fromImage(qi);
    mpImageLabel->setPixmap(mPixmap);
    update();
    qi.save(QString("Frame%1.png").arg(mFrameCount, 3, '0'));
    ++mFrameCount;
}

QAction *SandboxMainWindow::action(const Key &key)
{
    return actions()->action(key);
}

void SandboxMainWindow::setupActions()
{
    qInfo() << Q_FUNC_INFO;
 //   ActionManager::Action actQuit = actions()->add("Main/Quit");
//    toolBar()->addAction(actQuit);

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
