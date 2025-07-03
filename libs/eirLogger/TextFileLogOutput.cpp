#include "TextFileLogOutput.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QUrl>

#include <AText.h>
#include <FileInfo.h>

TextFileLogOutput::TextFileLogOutput(QObject *parent)
    : BaseLogOutput{parent}
{
    setObjectName("StdioLogOutput:{null}");
}

TextFileLogOutput::TextFileLogOutput(const QUrl &url, QObject *parent)
    : BaseLogOutput{url, parent}
{
    setObjectName("StdioLogOutput:" + mUrl.toString());
}

void TextFileLogOutput::start()
{

}

void TextFileLogOutput::writeLine(const LogItem li)
{
    const LogContext cItemContext  = li.context();
    if (mCurrentContext.qFuncInfo() == cItemContext.qFuncInfo())
    {
        const AText cContextText = ">>>"
                + cItemContext.qFuncInfo()
                + " @" +cItemContext.baseFileName();
        writeLine(cContextText, li);
    }
}

void TextFileLogOutput::open(const FileInfo &fi)
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

void TextFileLogOutput::openStdio()
{
    close();
    mpInfoStream = new QTextStream(stdout);
    mpErrorStream = new QTextStream(stderr);
    Q_CHECK_PTR(mpInfoStream);
    Q_CHECK_PTR(mpErrorStream);
}

void TextFileLogOutput::close()
{
    if (mpFile) mpFile->close();
    if (mpFile) mpFile->deleteLater();
    if (mpInfoStream) delete mpInfoStream;
    if (mpErrorStream) delete mpErrorStream;
    mpFile = nullptr;
    mpInfoStream = mpErrorStream = nullptr;
}

void TextFileLogOutput::writeLine(const AText &at, const LogItem &li)
{
    if (li.isWarn())
        *mpErrorStream << at + '\n';
    else
        *mpInfoStream << at + '\n';
}
