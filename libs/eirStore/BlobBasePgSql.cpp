#include "BlobBasePgSql.h"

#include "AbstractBlobBase.h"

BlobBasePgSql::BlobBasePgSql(const Url &storeUrl, QObject *parent)
    : AbstractBlobBase{storeUrl, parent}
{
    setObjectName("BlobPgSqlDatabase:" + mUrl.toString());

}

bool BlobBasePgSql::create(const bool force)
{
    bool result = false;

    return result;

}


bool BlobBasePgSql::open()
{
    bool result = false;

    return result;
}

bool BlobBasePgSql::contains(const Uid &uid)
{
    bool result = false;

    return result;
}

BlobItem BlobBasePgSql::read(const Uid &uid)
{
    BlobItem result;

    return result;
}

bool BlobBasePgSql::write(const Uid &uid, const BlobItem &item)
{
    bool result = false;

    return result;
}
