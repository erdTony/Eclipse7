#include "LogFile.h"

#include <CText.h>
#include <CTextList.h>

LogFile::LogFile() { clear();}
LogFile::LogFile(FILE *pFile) { set(pFile); }
LogFile::LogFile(const QString &pathname)  { set(pathname); }
LogFile::LogFile(const QDir &dir, const QString &filename) { set(dir, filename); }

FSText LogFile::filePath() const
{
    return (isSet()) ? FSText(mFileInfo.filePath()) : FSText();
}

QDir LogFile::dir() const
{
    return (isSet()) ? mFileInfo.dir() : QDir();
}

FSText LogFile::baseFileName() const
{
    return (isSet()) ? FSText(mFileInfo.baseName()) : FSText();
}

FSText LogFile::fileName() const
{
    return (isSet()) ? FSText(mFileInfo.fileName()) : FSText();
}

FSText LogFile::absoluteFilePath() const
{
    return (isSet()) ? FSText(mFileInfo.absoluteFilePath()) : FSText();
}

FSText LogFile::lastPathSegment() const
{
    return mPathSegments.isEmpty() ? FSText() : mPathSegments.last();
}

FSText LogFile::pathSegment(const int ix) const
{
    return (ix > 0 && ix < mPathSegments.count())
               ? mPathSegments.value(ix) : FSText();
}

void LogFile::clear()
{
    mSet.reset();
    mpStdioFile = nullptr;
    mFileInfo.setFile("");
    mDir = QDir();
    mPathSegments.clear();
}

void LogFile::replace(const char ch, const FSText &tx)
{
    if (mFileInfo.path().contains(ch))
    {
        QString tPath = mFileInfo.path();
        tPath.replace(ch, tx());
        mFileInfo.setFile(tPath);
    }
}

void LogFile::setBaseFileName(const FSText &tx)
{
    mFileInfo.setFile(tx);
}

void LogFile::setSuffix(const FSText &tx)
{
    mFileInfo.setFile(mFileInfo.baseName() + "." + tx());
}

void LogFile::set(FILE *pFile)
{
    clear();
    mSet.set();
    mpStdioFile = pFile;
}

void LogFile::set(const QString &pathname)
{
    clear();
    mSet.set();
    mFileInfo.setFile(pathname);
    mDir = mFileInfo.dir();
    mPathSegments = mDir.path().split('/');
}

void LogFile::set(const QDir &dir, const QString &filename)
{
    clear();
    mSet.set();
    mFileInfo.setFile(dir, filename);
    mDir = mFileInfo.dir();
    mPathSegments = mDir.path().split('/');
}

void LogFile::start()
{
    if (mpStdioFile) return;
    close();
    mpFile = new QFile(filePath());
    Q_CHECK_PTR(mpFile);
    if (mpFile->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        mpFile->write("Started\n\n");
    }
    else
    {
        close();
    }
}

void LogFile::write(const CTextList &ctxl)
{
    if (mpStdioFile)
        foreach (const CText cCtx, ctxl)
        {
            std::fprintf(mpStdioFile, "%s\n", cCtx.constData());
        }
    if (mpFile)
        foreach (const CText cCtx, ctxl)
        {
            mpFile->write(cCtx);
            mpFile->write("\n");
        }
}

void LogFile::flush()
{
    if (mpStdioFile) return;
    if (mpFile)
        mpFile->flush();
}

void LogFile::close()
{
    if (mpStdioFile) return;
    if (mpFile)
    {
        mpFile->flush();
        mpFile->close();
        mpFile->deleteLater();
        mpFile = nullptr;
    }
}



