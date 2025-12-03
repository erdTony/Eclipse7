#include "BlobBaseSqlLite.h"

#include "AbstractBlobBase.h"

BlobBaseSqlLite::BlobBaseSqlLite(const Url &storeUrl, QObject *parent)
    : AbstractBlobBase{storeUrl, parent}
{
    setObjectName("BlobSqlLiteDatabase:" + mUrl.toString());

}

bool BlobBaseSqlLite::create(const bool force)
{
    bool result = false;

    return result;

}


bool BlobBaseSqlLite::open()
{
    bool result = false;

    return result;
}

bool BlobBaseSqlLite::contains(const Uid &uid)
{
    bool result = false;

    return result;
}

BlobItem BlobBaseSqlLite::read(const Uid &uid)
{
    BlobItem result;

    return result;
}

bool BlobBaseSqlLite::write(const Uid &uid, const BlobItem &item)
{
    bool result = false;

    return result;
}
