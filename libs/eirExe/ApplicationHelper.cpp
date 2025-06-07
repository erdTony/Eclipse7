#include "ApplicationHelper.h"

#include <QCoreApplication>

#include "CommandLine.h"
#include "KeySegList.h"
#include "Options.h"
#include "Settings.h"

ApplicationHelper::ApplicationHelper(QObject *parent)
    : QObject{parent}
    , mpCommandLine(new CommandLine(this))
    , mpOptions(new Options(this))
    , mpSettings(new Settings(this))
{
    setObjectName("ApplicationHelper:" + QCoreApplication::applicationName());
}

void ApplicationHelper::add(const QCommandLineOption opt)
{
    opts()->add(opt);
}

void ApplicationHelper::add(const OptionList opts)
{
    foreach (const QCommandLineOption cOpt, opts) add(cOpt);
}

void ApplicationHelper::addOption(const KeySeg &name)
{
    opts()->add(QCommandLineOption(name));
}

void ApplicationHelper::addOption(const KeySegList &names)
{
    opts()->add(QCommandLineOption(names.toStringList()));
}

void ApplicationHelper::addOption(const KeySeg &name, const QString &desc)
{
    opts()->add(QCommandLineOption(name, desc));
}

void ApplicationHelper::addOption(const KeySegList &names, const QString &desc)
{
    opts()->add(QCommandLineOption(names.toStringList(), desc));
}
