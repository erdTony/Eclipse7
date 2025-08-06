#include "FileEnumerator.h"


#include <QFileSystemModel>
#include <QTimer>

FileEnumerator::FileEnumerator(const FileEnumeratorParms &fed, QObject *parent)
    : QObject{parent}
    , mParms(fed)
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
    if (mpModel->canFetchMore(mFetchIndex))
    {
        Count tFetchCount = parms().collectChunk();
        do
        {
            mpModel->fetchMore(mFetchIndex);
            qDebug() << mFetchIndex;
        } while (mpModel->canFetchMore(mFetchIndex)
                 && --tFetchCount);
    }
}

void FileEnumerator::pulseEnumerate()
{

}


