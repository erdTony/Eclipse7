#include "BlobSqlLiteDatabase.h"

#include "AbstractBlobDatabase.h"

BlobSqlLiteDatabase::BlobSqlLiteDatabase(const Url &storeUrl, QObject *parent)
    : AbstractBlobDatabase{storeUrl, parent}
{
    setObjectName("BlobSqlLiteDatabase:" + mUrl.string());

}


bool BlobSqlLiteDatabase::open()
{
    bool result = false;

    return result;
}

bool BlobSqlLiteDatabase::contains(const Uid &uid)
{
    bool result = false;

    return result;
}

BlobItem BlobSqlLiteDatabase::read(const Uid &uid)
{
    BlobItem result;

    return result;
}

bool BlobSqlLiteDatabase::write(const Uid &uid, const BlobItem &item)
{
    bool result = false;

    return result;
}
