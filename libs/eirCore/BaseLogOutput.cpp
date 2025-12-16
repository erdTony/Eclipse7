#include "BaseLogOutput.h"


#include <QTimer>

#include <CTextList.h>

#include "LogItem.h"

BaseLogOutput::BaseLogOutput(QObject *parent) : QObject{parent} {;}
BaseLogOutput::BaseLogOutput(const CText &url, QObject *parent)
    : QObject{parent}, mUrl(url) { start(url); }

void BaseLogOutput::start(const CText &url)
{
//    mUrl.set(LogUrl::LogOut, url);
}

void BaseLogOutput::write(const LogItem &li)
{
    mUrl.file().write(CTextList(li.displayString()));
}

void BaseLogOutput::write(const CTextList &ctxl)
{
    mUrl.file().write(ctxl);

}

void BaseLogOutput::flush()
{
    mUrl.file().flush();

}

void BaseLogOutput::close()
{
    mUrl.file().close();

}

