#include "ExeSupport.h"

#include <QCoreApplication>


#include "ActionManager.h"
#include "CommandLine.h"
#include "CTextList.h"
#include "Options.h"
#include "Random.h"
#include "Settings.h"

ExeSupport::ExeSupport(QCoreApplication *app)
    : mpCoreApplication(app)
    , mpActionManager(new ActionManager(app))
    , mpCommandLine(new CommandLine(app))
    , mpOptions(new Options(app))
    , mpRandom(new Random(app))
    , mpSettings(new Settings(app))
{
}

bool ExeSupport::contains(const CText &name)
{
    return false; // TODO ExeSupport::contains(name)
}

QString ExeSupport::positional(const CText &name)
{

    return QString(); // TODO ExeSupport::positional(name)
}

QString ExeSupport::positional(const Index ix)
{

    return QString(); // TODO ExeSupport::positional(ix)
}

void ExeSupport::add(const QCommandLineOption opt)
{
    opts()->add(opt);
}

void ExeSupport::add(const OptionList opts)
{
    foreach (const QCommandLineOption cOpt, opts) add(cOpt);
}

void ExeSupport::addOption(const CText &name)
{
    opts()->add(QCommandLineOption(name()));
}

void ExeSupport::addOption(const CTextList &names)
{
    opts()->add(QCommandLineOption(names.toStringList()));
}

void ExeSupport::addOption(const CText &name, const QString &desc)
{
    opts()->add(QCommandLineOption(name(), desc));
}

void ExeSupport::addPositional(const CText &name, const QString &desc)
{
    opts()->add(name, desc);
}

void ExeSupport::addOption(const CTextList &names, const QString &desc)
{
    opts()->add(QCommandLineOption(names.toStringList(), desc));
}

void ExeSupport::addShowOptions()
{
    addOption(CText("showmin"), "Show Applicaion Minimized to Tray");
    addOption(CText("showmax"), "Show Applicaion Maximized to Screen");
    addOption(CText("shownorm"), "Show Applicaion as Normal Window");
}

void ExeSupport::addHelpVerOptions()
{
    opts()->addHelp();
    opts()->addVersion();
}

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
