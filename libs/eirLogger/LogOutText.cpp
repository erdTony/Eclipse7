#include "LogOutText.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QUrl>

#include <AText.h>
#include <CText.h>
#include <CTextList.h>
#include <LogFileInfo.h>

LogOutText::LogOutText(const bool openStd,
                       const bool oneLine,
                       QObject *parent)
    : LogOutput{openStd ? "StdIO" : "@.log",
                oneLine ? LogFormat::TextOneLine : LogFormat::TextMultiLine,
                parent}
{
    setObjectName("StdioLogOutput:" + name()());
    if (openStd)
        openStdio();
    else
        open(LogFileInfo("./log/&-@.log"));
}

void LogOutText::start()
{

}

void LogOutText::write(const LogItem &li)
{
    Q_UNUSED(li); // TODO
}

void LogOutText::write(const CTextList &ctxl)
{
#if 1
    foreach (const CText cCtx, ctxl)
    {
        file()->write(cCtx);
        file()->write("\n");
    }
#else // compiler wont text stream a byte array?!?
    foreach (const CText cCtx, ctxl)
        mpInfoStream << QByteArray(cCtx) << Qt::endl;
#endif
    // TODO deal with severity
}

void LogOutText::open(const LogFileInfo &lfi)
{
    close();
    AText tFilePath = lfi.filePath();
    tFilePath.replace('&',
        QCoreApplication::applicationName().toLocal8Bit());
    tFilePath.replace('@', QDateTime::currentDateTime()
        .toString("DyyyyMMdd-Thhmm").toLocal8Bit());
    mpFile = new QFile(tFilePath, this);
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

