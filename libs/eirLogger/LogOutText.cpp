#include "LogOutText.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QUrl>

#include <AText.h>
#include <LogFileInfo.h>

LogOutText::LogOutText(const bool openStd, QObject *parent)
    : LogOutput{openStd ? "StdIO" : "{null}", LogFormat::$nullFormat, parent}
{
    setObjectName("StdioLogOutput:" + name()());
    if (openStd) openStdio();
}

void LogOutText::start()
{

}

void LogOutText::write(const LogItem &li)
{
    Q_UNUSED(li); // TODO
}

void LogOutText::open(const LogFileInfo &lfi)
{
    close();
    mpFile = new QFile(lfi.filePath(), this);
    Q_CHECK_PTR(mpFile);
    if (mpFile->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        mpInfoStream = new QTextStream(mpFile);
        mpErrorStream = new QTextStream(mpFile);
        Q_CHECK_PTR(mpInfoStream);
        Q_CHECK_PTR(mpErrorStream);
    }
}

void LogOutText::openStdio()
{
    close();
    mpInfoStream = new QTextStream(stdout);
    mpErrorStream = new QTextStream(stderr);
    Q_CHECK_PTR(mpInfoStream);
    Q_CHECK_PTR(mpErrorStream);
}

void LogOutText::close()
{
    if (mpFile) mpFile->close();
    if (mpFile) mpFile->deleteLater();
    if (mpInfoStream) delete mpInfoStream;
    if (mpErrorStream) delete mpErrorStream;
    mpFile = nullptr;
    mpInfoStream = mpErrorStream = nullptr;
}

