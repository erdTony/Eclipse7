#include "LogOutput.h"

#include <CTextList.h>


LogOutput::LogOutput(QObject *parent) : QObject{parent} {;}
LogOutput::LogOutput(const CText &url, QObject *parent)
    : QObject{parent} { start(url); }

void LogOutput::start(const CText &url)
{
    mUrl.set(LogUrl::LogOut, url);
}

void LogOutput::write(const LogItem &li)
{
    mUrl.file().write(CTextList(li.displayString()));
}

void LogOutput::write(const CTextList &ctxl)
{
    mUrl.file().write(ctxl);

}

void LogOutput::flush()
{
    mUrl.file().flush();

}

void LogOutput::close()
{
    mUrl.file().close();

}

