#include "EfpImageReader.h"

#include <QFileSystemModel>

#include <Log.h>

EfpImageReader::EfpImageReader(const Url &url, QObject *parent)
    : QObject{parent}
{
    setObjectName("EfpImageReader:" + url.toString());
    inputUrl(url);
}

void EfpImageReader::initialize()
{
    if (mUseModel)
        mpFSModel = new QFileSystemModel(this);
    INFOMSG("Initializing File System Model");
    emit initialized();
}

void EfpImageReader::setup()
{
    if (mInputDir.isReadable() && ! mUseModel)
    {
        QFileInfoList tFIList = mInputDir.entryInfoList();
        mFileInfoList = tFIList;
    }
    emit setupd();
}

void EfpImageReader::start()
{

    emit started();
}

void EfpImageReader::pause()
{

    emit paused();
}

void EfpImageReader::resume()
{

    emit resumed();
}

void EfpImageReader::inputDir(const QDir &dir)
{
    mInputDir = QDir();
    if (dir.isReadable())
    {
        QStringList tNameFilters;
        tNameFilters << "*.jpg" << "*.png" << "*.bmp";
        QDir::Filters tEntryFilters = QDir::Files;
        if (mDirDepth != 1) tEntryFilters |= QDir::Dirs;
        QDir::SortFlags tSortFlags = QDir::NoSort;
        mInputDir = dir;
        mInputDir.setNameFilters(tNameFilters);
        mInputDir.setFilter(tEntryFilters);
        mInputDir.setSorting(tSortFlags);
    }
}

void EfpImageReader::inputUrl(const Url &url)
{

    mInputUrl = url;
    mUseModel = ! url.contains("Direct");
    mSampleMsec = 100;
    mDirDepth = 1;
    // TODO set mSampleTime from url
    // TODO set suffix list from url
    // TODO set dir depth from url
    // TODO set dir sort from url
    inputDir(url.pathDir());

}
