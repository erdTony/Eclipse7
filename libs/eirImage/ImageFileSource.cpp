#include "ImageFileSource.h"

#include <QTimer>

#include <Log.h>

ImageFileSource::ImageFileSource(QObject *parent)
    : QFileSystemModel{parent}
{
    FNENTER();
    setObjectName("ImageFileSource");
}

void ImageFileSource::clear()
{
    FNSLOT();
    if (mpPulseTimer)
    {
        DISCON(mpPulseTimer, SIGNAL(&QTimer::timeout()),
                   this, SLOT(&ImageFileSource::pulse));
        mpPulseTimer->stop();
        mpPulseTimer->deleteLater();
        mpPulseTimer = nullptr;
    }
    mFlags = $null;
    mRootDir = QDir();
    mFetchIndex = QModelIndex();
    mFetchQueue.clear();
    mImageQueue.clear();
}

void ImageFileSource::start(const QDir &rootDir)
{
    FNSLOT();
    FNARG(rootDir.path());
    clear();
    mRootDir = rootDir;
    setObjectName("ImageFileSource:" + mRootDir.path());
    Q_ASSERT(nullptr==mpPulseTimer);
    mpPulseTimer = new QTimer(this);
    CONNECT(mpPulseTimer, SIGNAL(&QTimer::timeout),
            this, SLOT(&ImageFileSource::pulse));
    CONNECT(this, SIGNAL(&QFileSystemModel::canFetchMore),
            this, SLOT(&ImageFileSource::fetch));
    mpPulseTimer->start(250);
    emit starting(rootDir);
    QFileSystemModel::setReadOnly(true);
    QFileSystemModel::setRootPath(rootDir.path());
}

void ImageFileSource::fetch()
{
    FNSLOT();
    fetchMore(mFetchIndex);
    mFlags |= Fetching;
}

void ImageFileSource::pulse()
{
    FNSLOT();
    if (mFlags & Fetching)
        pulseFetch();
}

void ImageFileSource::pulseFetch()
{
    if (mFetchQueue.count() > 32)   return;

    int tCount = 16;
    while (mFetchIndex.row() < rowCount(mFetchIndex) && tCount)
    {
        const QFileInfo cFI = fileInfo(mFetchIndex);
        mFetchIndex = index(1 + mFetchIndex.row(),
                            mFetchIndex.column(),
                            mFetchIndex);
        --tCount;
    }

    if (mFetchIndex.row() >= rowCount(mFetchIndex))
        mFlags &= ~ Fetching;
}


