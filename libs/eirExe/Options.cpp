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
        mKeyOptionMap.insert(KeySeg(csSeg), opt);
}
