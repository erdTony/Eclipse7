#include "ExeSupport.h"

#include <QCoreApplication>

#include <CTextList.h>

#include "ActionManager.h"
#include "CommandLine.h"
#include "Options.h"
#include "Random.h"
#include "Settings.h"

ExeSupport::ExeSupport(QCoreApplication *capp)
    : mpConsoleApplication(capp)
{
    initialize(capp);
}

ExeSupport::ExeSupport(QApplication *wapp)
    : mpWidgetApplication(wapp)
{
    initialize((QObject *)(wapp));
}

void ExeSupport::initialize(QObject * parent)
{
    mpActionManager = new ActionManager(parent);
    mpCommandLine = new CommandLine(parent);
    mpOptions = new Options(parent);
    mpRandom = new Random(parent);
    mpSettings = new Settings(parent);
    Q_CHECK_PTR(mpActionManager);
    Q_CHECK_PTR(mpCommandLine);
    Q_CHECK_PTR(mpOptions);
    Q_CHECK_PTR(mpRandom);
    Q_CHECK_PTR(mpSettings);
}

/*
void ExeSupport::setup()
{
    opts()->setup();
    cli()->setup();
    stgs()->setup();
    rand()->setup();
    act()->setup();
}

void ExeSupport::execute()
{
    opts()->execute();
    cli()->execute();
    stgs()->execute();
    rand()->execute();
    act()->execute();

}
*/

