#include "Options.h"

#include <QCoreApplication>

#include <KeySeg.h>

Options::Options(QObject *parent)
    : QObject{parent}
{
    setObjectName("Options:" + QCoreApplication::applicationName());

}

void Options::add(const QCommandLineOption opt)
{
    foreach (const QString csSeg, opt.names())
    {
        mKeyOptionMap.insert(KeySeg(csSeg), opt);
        emit added(opt);
    }
}

void Options::add(const KeySeg &name, const QString &desc)
{
    mPositionalList.append(Positional(name, desc));
    emit added(name);
}

void Options::addHelp()
{
    parser().addHelpOption();
}

void Options::addVersion()
{
    parser().addVersionOption();
}

void Options::setup()
{

}

void Options::execute()
{

}
