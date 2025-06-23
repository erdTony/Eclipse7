#include "BaseLogOutput.h"


BaseLogOutput::BaseLogOutput(QObject *parent)
    : QObject{parent}
{}

BaseLogOutput::BaseLogOutput(const QUrl &url, QObject *parent)
    : QObject{parent}
    , mUrl(url)
{
    setObjectName("BaseLogOutput:" + mUrl.toString());
}

void BaseLogOutput::start(const QUrl &url)
{
    mUrl = url;
    setObjectName("BaseLogOutput:" + mUrl.toString());
    start();
}
