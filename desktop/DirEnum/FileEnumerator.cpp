#include "FileEnumerator.h"


#include <QFileSystemModel>
#include <QTimer>

FileEnumerator::FileEnumerator(QObject *parent)
    : QObject{parent}
    , mpModel(new QFileSystemModel(parent))
{
    setObjectName("FileEnumerator");
    mpModel->setObjectName("QFileSystemModel");
}

void FileEnumerator::start(const Url &url)
{
    mBaseDir = url.dir();
    if ( ! mBaseDir.exists())
    {
        emit error(mBaseDir.absolutePath() + " does not exist");
        return;
    }
    mpModel->setReadOnly(true);
    mFetchIndex = mpModel->setRootPath(mBaseDir.absolutePath());
    QTimer::singleShot(100, this, &FileEnumerator::pulse);
}

void FileEnumerator::pulse()
{
    const Count cFetchUpper = 128;
    const Count cFetchLower = 32;
    const Count cFetchChunk = 8;

    if (mpModel->canFetchMore(mFetchIndex))
    {
        Count tFetchCount = cFetchChunk;
        do
        {
            mpModel->fetchMore(mFetchIndex);
            qDebug() << mFetchIndex;
        } while (mpModel->canFetchMore(mFetchIndex)
                 && --tFetchCount);
    }
}


