#include "AbstractLogOutput.h"


AbstractLogOutput::AbstractLogOutput(QObject *parent)
    : QObject{parent}
{}

AbstractLogOutput::AbstractLogOutput(const QUrl &url, QObject *parent)
    : QObject{parent}
    , mUrl(url)
{
    setObjectName("BaseLogOutput:" + mUrl.toString());
}

void AbstractLogOutput::start(const QUrl &url)
{
    mUrl = url;
    setObjectName("BaseLogOutput:" + mUrl.toString());
    start();
}
