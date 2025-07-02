#include "SandboxApplication.h"

#include <QTimer>
#include <QToolBar>

#include <ActionManager.h>
#include <ExeSupport.h>
#include <Image.h>

#include "SandboxEngine.h"
#include "SandboxMainWindow.h"

SandboxApplication::SandboxApplication(int &argc, char **argv)
    : BaseWidgetApplication{argc, argv}
{
    qInfo() << Q_FUNC_INFO;
    setObjectName("SandboxApplication:" + applicationName());
}

void SandboxApplication::initialize()
{
    qInfo() << Q_FUNC_INFO;

    mpEngine = new SandboxEngine(this);
    engine()->initialize();

    connect(this, &SandboxApplication::initialized,
            mainWindow(), &SandboxMainWindow::initialize);
    connect(mainWindow(), &SandboxMainWindow::initialized,
            this, &SandboxApplication::objconnect);

    emit initialized();
}

void SandboxApplication::objconnect()
{
    qInfo() << Q_FUNC_INFO;
    connect(this, &SandboxApplication::objconnected,
            this, &SandboxApplication::configure);
    connect(this, &SandboxApplication::configured,
            mainWindow(), &SandboxMainWindow::configure);
    connect(mainWindow(), &SandboxMainWindow::configured,
            this, &SandboxApplication::setup);
    connect(this, &SandboxApplication::setuped,
            mainWindow(), &SandboxMainWindow::setup);
    connect(mainWindow(), &SandboxMainWindow::setuped,
            this, &SandboxApplication::start);
    connect(this, &SandboxApplication::started,
            mainWindow(), &SandboxMainWindow::start);
    connect(engine(), &SandboxEngine::passComplete,
            mainWindow(), &SandboxMainWindow::pass);
    connect(engine(), &SandboxEngine::finished,
            engine(), &SandboxEngine::flip);
    emit objconnected();
}

void SandboxApplication::configure()
{
    qInfo() << Q_FUNC_INFO;
    // TODO: Process CommandLine
    // TODO: Open ApplicationSettings from OrgAppIni and CLArgs
    // TODO: Read SandboxData from settings
    engine()->configure();
    emit configured();
}

void SandboxApplication::setup()
{
    qInfo() << Q_FUNC_INFO;

    engine()->setup();
    QImage tSubjectImage(":/image/MM512A.jpg");
    engine()->setSubjectImage(BaseImage(Image::Color, tSubjectImage));

    emit setuped();
}

void SandboxApplication::start()
{
    qInfo() << Q_FUNC_INFO;
    QTimer::singleShot(2000, engine(), &SandboxEngine::start);
    emit started();
}

void SandboxApplication::actQuit(const bool checked)
{
    qInfo() << Q_FUNC_INFO;
    Q_UNUSED(checked);
    exit(0);
}

SandboxScene *SandboxApplication::scene()
{
    return mainWindow()->scene();
}

CommandLine *SandboxApplication::commandLine()
{
    return exe()->cli();
}

Settings *SandboxApplication::settings()
{
    return exe()->stgs();
}
