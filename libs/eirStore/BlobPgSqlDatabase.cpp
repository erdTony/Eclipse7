#include "BlobPgSqlDatabase.h"

#include "AbstractBlobDatabase.h"

BlobPgSqlDatabase::BlobPgSqlDatabase(const Url &storeUrl, QObject *parent)
    : AbstractBlobDatabase{storeUrl, parent}
{
    setObjectName("BlobPgSqlDatabase:" + mUrl.string());

}


bool BlobPgSqlDatabase::open()
{
    bool result = false;

    return result;
}

bool BlobPgSqlDatabase::contains(const Uid &uid)
{
    bool result = false;

    return result;
}

BlobItem BlobPgSqlDatabase::read(const Uid &uid)
{
    BlobItem result;

    return result;
}

bool BlobPgSqlDatabase::write(const Uid &uid, const BlobItem &item)
{
    bool result = false;

    return result;
}
