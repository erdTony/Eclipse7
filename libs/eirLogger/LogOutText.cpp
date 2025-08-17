#include "LogOutText.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QUrl>

#include <AText.h>
#include <LogFileInfo.h>

LogOutText::LogOutText(const bool openStd, QObject *parent)
    : AbstractLogOutput{parent}
{
    setObjectName(QString("StdioLogOutput:%1")
            .arg(openStd ? "StdIO" : "{null}"));
    if (openStd)
        openStdio();
}

void LogOutText::start()
{

}

void LogOutText::writeLine(const LogItem li)
{
}

void LogOutText::open(const LogFileInfo &fi)
{
    close();
    mpFile = new QFile(fi.filePath(), this);
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

void LogOutText::writeLine(const AText &at, const LogItem &li)
{
    if (li.isWarn())
        *mpErrorStream << at + '\n';
    else
        *mpInfoStream << at + '\n';
}
