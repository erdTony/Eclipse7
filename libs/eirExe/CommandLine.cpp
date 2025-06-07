#include "CommandLine.h"

#include <QCoreApplication>


CommandLine::CommandLine(QObject *parent)
    : QObject{parent}
{
    setObjectName("CommandLine:" + QCoreApplication::applicationName());

}
