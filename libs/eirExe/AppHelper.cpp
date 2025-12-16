#include "AppHelper.h"

#include <QApplication>


#include "ActionManager.h"
#include "CommandLine.h"
#include "Options.h"
#include "Random.h"
#include "Settings.h"


AppHelper::AppHelper(QCoreApplication *capp)
    : QObject{capp}
{
    setObjectName("AppHelper:ConsoleApp:"
                  + QCoreApplication::applicationName());
    initialize();
}

AppHelper::AppHelper(QApplication *wapp)
    : QObject{wapp}
{
    setObjectName("AppHelper:WidgetApp:"
                  + QCoreApplication::applicationName());
    initialize();
}

void AppHelper::initialize()
{
    mpActionManager = new ActionManager;
    mpCommandLine = new CommandLine(this);
    mpOptions = new Options(this);
    mpRandom = new Random(this);
    mpSettings = new Settings(this);
    Q_CHECK_PTR(mpActionManager);
    Q_CHECK_PTR(mpCommandLine);
    Q_CHECK_PTR(mpOptions);
    Q_CHECK_PTR(mpRandom);
    Q_CHECK_PTR(mpSettings);
    emit initialized();
}

QCoreApplication *AppHelper::core()
{
    if (isConsoleApp()) return capp();
    if (isWidgetApp()) return (QCoreApplication *)wapp();
    return nullptr;
}
