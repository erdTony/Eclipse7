#pragma once

#include <QSharedData>
#include <DataProperty.h>

#include <DirInfo.h>
#include <MillisecondTime.h>
#include <Types.h>
#include <Url.h>

#define FILEENUMDATA_DATAPROPS(TND) \
    TND(Url, sourceUrl, Url()) \
    TND(DirInfo, sourceDir, DirInfo()) \
    TND(Milliseconds, shortPulseMsec, 10) \
    TND(Milliseconds, longPulseMsec, 1000) \
    TND(Count, collectUpper, 96) \
    TND(Count, collectLower, 32) \
    TND(Count, collectChunk, 8) \
    TND(Count, readUpper, 96) \
    TND(Count, readLower, 32) \
    TND(Count, readChunk, 8) \
    TND(Count, loadUpper, 96) \
    TND(Count, loadLower, 32) \
    TND(Count, loadChunk, 8) \
    TND(Count, cacheUpper, 96) \
    TND(Count, cacheLower, 32) \
    TND(Count, cacheChunk, 8) \

class FileEnumeratorParmsData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(FILEENUMDATA_DATAPROPS);
public:
    FileEnumeratorParmsData(void)
    {
        DEFINE_DATAPROPS_CTORS(FILEENUMDATA_DATAPROPS);
    }
};

class FileEnumeratorParms
{
    DECLARE_PARENT_DATAPROPS(FILEENUMDATA_DATAPROPS);
    DECLARE_DATAPROPS(FileEnumeratorParms, FileEnumeratorParmsData);
    // alternate ctor: FileEnumeratorParms(const int size);
};
