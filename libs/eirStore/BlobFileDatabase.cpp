#include "BlobFileDatabase.h"

BlobFileDatabase::BlobFileDatabase(const Url storeUrl,QObject *parent)
    : AbstractBlobDatabase{storeUrl, parent}
{
    setObjectName("BlobFileDatabase:" + mUrl.string());

}

bool BlobFileDatabase::open()
{
    bool result = false;

    return result;

}

bool BlobFileDatabase::contains(const Uid &uid)
{
    bool result = false;

    return result;

}

BlobItem BlobFileDatabase::read(const Uid &uid)
{
    BlobItem result;

    return result;

}

bool BlobFileDatabase::write(const Uid &uid, const BlobItem &item)
{
    bool result = false;

    return result;

}
