#include "Settings.h"

#include <QCoreApplication>


Settings::Settings(QObject *parent)
    : QObject{parent}
{
    setObjectName("Settings:" + QCoreApplication::applicationName());

}
