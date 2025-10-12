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
    mRootDir = QDir();
    mCurrentIndex = QModelIndex();
    mFIQueue.clear();
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

}

void ImageFileSource::pulse()
{
    FNSLOT();

}
