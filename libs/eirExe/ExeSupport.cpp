#include "ExeSupport.h"

#include <QCoreApplication>


#include "ActionManager.h"
#include "CommandLine.h"
#include "KeySegList.h"
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

void ExeSupport::add(const QCommandLineOption opt)
{
    opts()->add(opt);
}

void ExeSupport::add(const OptionList opts)
{
    foreach (const QCommandLineOption cOpt, opts) add(cOpt);
}

void ExeSupport::addOption(const KeySeg &name)
{
    opts()->add(QCommandLineOption(name));
}

void ExeSupport::addOption(const KeySegList &names)
{
    opts()->add(QCommandLineOption(names.toStringList()));
}

void ExeSupport::addOption(const KeySeg &name, const QString &desc)
{
    opts()->add(QCommandLineOption(name, desc));
}

void ExeSupport::addOption(const KeySegList &names, const QString &desc)
{
    opts()->add(QCommandLineOption(names.toStringList(), desc));
}
