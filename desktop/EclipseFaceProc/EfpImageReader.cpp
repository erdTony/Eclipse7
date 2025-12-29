#include "EfpImageReader.h"

#include <QFileSystemModel>
#include <QTimer>

#include <Log.h>

EfpImageReader::EfpImageReader(QObject *parent)
    : QObject{parent}
    , mpCaptureTimer(new QTimer(this))
{
    FNENTER();
    qInfo() << Q_FUNC_INFO;
    Q_CHECK_PTR(mpCaptureTimer);
    setObjectName("EfpImageReader");
}

void EfpImageReader::initialize()
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO;
    Q_CHECK_PTR(mpCaptureTimer);
    connect(mpCaptureTimer, &QTimer::timeout,
            this, &EfpImageReader::capture);
    mSampleMsec = 1000;
    mDirDepth = 1;
}

void EfpImageReader::setup()
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO;
    if (inputDir().isReadable() && ! mUseModel)
    {
        // TODO Show Something
    }
    // TODO else mUseModel
    emit setupd();
}

void EfpImageReader::start(const QDir &dir)
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO << dir.path();
    queryInputDir(dir);
    Q_CHECK_PTR(mpCaptureTimer);
    mpCaptureTimer->start(mSampleMsec);
    emit started();
}

void EfpImageReader::pause()
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO;
    Q_CHECK_PTR(mpCaptureTimer);
    mpCaptureTimer->stop();
    mPaused = true;
    emit paused();
}

void EfpImageReader::resume()
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO;
    Q_CHECK_PTR(mpCaptureTimer);
    mpCaptureTimer->start();
    mPaused = false;
    emit resumed();
}

void EfpImageReader::capture()
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO << mFileInfoList.count() << mPaused;
    if (mPaused) return;
    if (mFileInfoList.isEmpty())
    {
        qInfo() << Q_FUNC_INFO << "finished";
        INFOMSG("emit finished()");
        pause();
        emit finished();
        return;
    }
    QFileInfo tFI = mFileInfoList.takeFirst();
    if (tFI.isReadable())
    {
        QImage tImage = QImage(tFI.filePath());
        if ( ! tImage.isNull())
        {
            qInfo() << Q_FUNC_INFO << "captured" << tFI.baseName();
            INFOMSG("emit captured(): " + tFI.filePath());
            emit captured(tFI, tImage);
        }
    }
    if (mLoop)
        mFileInfoList.append(tFI);
}

bool EfpImageReader::queryInputDir(const QDir &dir)
{
    bool result = false;
    mInputDir = QDir();
    qInfo() << Q_FUNC_INFO << dir.path();
    QDir tInputDir = dir;
    qInfo() << Q_FUNC_INFO << tInputDir.path();
    if (tInputDir.isReadable())
    {
        QStringList tNameFilters;
        tNameFilters << "*.jpg" << "*.png" << "*.bmp";
        QDir::Filters tEntryFilters = QDir::Files;
        // TODO handle mDirDepth: if (mDirDepth != 1) tEntryFilters |= QDir::Dirs;
        QDir::SortFlags tSortFlags = QDir::NoSort;
        tInputDir.setNameFilters(tNameFilters);
        tInputDir.setFilter(tEntryFilters);
        tInputDir.setSorting(tSortFlags);
        qInfo() << Q_FUNC_INFO << tNameFilters << tEntryFilters << tSortFlags;
        mFileInfoList = tInputDir.entryInfoList(tNameFilters, tEntryFilters, tSortFlags);
        qInfo() << Q_FUNC_INFO << mFileInfoList.count();
        if ( ! mFileInfoList.isEmpty())
        {
            mInputDir = tInputDir;
            result = true;
        }
    }
    return result;
}
