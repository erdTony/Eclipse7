#pragma once
#include "eirStore.h"

#include <QSharedData>
#include <DataProperty.h>

#include <QByteArray>

#include <FSText.h>
#include <Id.h>
#include <Url.h>

#include "DirInfo.h"
#include "FileInfo.h"


#define FILEDATA_DATAPROPS(TND) \
    TND(Id, id, Id()) \
    TND(Url, sourceUrl, Url()) \
    TND(DirInfo, sourceDir, DirInfo()) \
    TND(FSText, fileName, FSText()) \
    TND(FileInfo, fileInfo, FileInfo()) \
    TND(QByteArray, fileBytes, QByteArray()) \

class FileDataData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(FILEDATA_DATAPROPS);
public:
    FileDataData(void)
    {
        DEFINE_DATAPROPS_CTORS(FILEDATA_DATAPROPS);
    }
};

class EIRSTORE_EXPORT FileData
{
    DECLARE_PARENT_DATAPROPS(FILEDATA_DATAPROPS);
    DECLARE_DATAPROPS(FileData, FileDataData);

public: // our ctors
    FileData(const Url &url, const FSText &fname);
    FileData(const DirInfo &dir, const FSText &fname);

public: // non-const
    void set(const Url &url, const FSText &fname);
    void set(const DirInfo &dir, const FSText &fname);

};
