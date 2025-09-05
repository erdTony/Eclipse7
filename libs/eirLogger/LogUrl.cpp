#include "LogUrl.h"

#include <QCoreApplication>
#include <QDateTime>

#include <FSText.h>

LogUrl::LogUrl() : mScheme($null) {;}
LogUrl::LogUrl(const Scheme s, const QString &u) { set(s, u); }

QString LogUrl::toString() const
{
    QUrl tUrl = mUrl;
    tUrl.setQuery(mQuery);
    return tUrl.toString();
}

void LogUrl::set(const Scheme s, QString u)
{
    if (u.isEmpty()) u = QString("../log/&-@.log");
    mScheme = s;
    switch (mScheme)
    {
    case LogOut:    setLogOut(u);       break;
    default:        /* nada */          break;
    }
}

void LogUrl::setLogOut(const QString &u)
{
    mUrl.setUrl(u);
    mQuery.setQuery(mUrl.query());
    mUrl.setQuery("");
    setFileInfo();
    setFilter();
    setFormat();
}

void LogUrl::setFileInfo()
{
    FSText tPath = mUrl.path().toLocal8Bit().toLower();
    if (tPath == "stdout")
        mLogFile.set(stdout);
    else if (tPath == "stderr")
        mLogFile.set(stderr);
    else
    {
        mLogFile.set(tPath);
        if (mLogFile.isDir())
        {
            mLogFile.setBaseFileName("&-@"),
                mLogFile.setSuffix("log");

        }
    }
    mLogFile.replace('&', QCoreApplication::applicationName());
    mLogFile.replace('@', QDateTime::currentDateTime()
                               .toString("DyyyyMMdd-Thhmm"));
}

void LogUrl::setFilter()
{
    if (mQuery.hasQueryItem("FilterMask"))
        mFilter.setMask(mQuery.queryItemValue("FilterMask"));
    if (mQuery.hasQueryItem("FilterMax"))
        mFilter.setMax(mQuery.queryItemValue("FilterMax"));
    if (mQuery.hasQueryItem("FilterMin"))
        mFilter.setMin(mQuery.queryItemValue("FilterMin"));
}

void LogUrl::setFormat()
{
    if (mQuery.hasQueryItem("Format"))
        mFormat.set(mQuery.queryItemValue("Format"));
}
