#include "BlobBaseFile.h"

BlobBaseFile::BlobBaseFile(const Url storeUrl,QObject *parent)
    : AbstractBlobBase{storeUrl, parent}
{
    setObjectName("BlobFileDatabase:" + mUrl.string());

}

bool BlobBaseFile::open()
{
    bool result = false;

    return result;

}

bool BlobBaseFile::contains(const Uid &uid)
{
    bool result = false;

    return result;

}

BlobItem BlobBaseFile::read(const Uid &uid)
{
    BlobItem result;

    return result;

}

bool BlobBaseFile::write(const Uid &uid, const BlobItem &item)
{
    bool result = false;

    return result;

}
