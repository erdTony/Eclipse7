#include "BlobStore.h"

#include <Log.h>

#include "BlobBaseFile.h"
#include "BlobBasePgSql.h"
#include "BlobBaseSqlLite.h"

BlobStore::BlobStore(QObject *parent)
    : QObject{parent}
{
    setObjectName("BlobStore");
}

BlobStore::BlobStore(const QString &storeUrl, QObject *parent)
    : QObject{parent}
{
    set(storeUrl);
}

bool BlobStore::set(const QString &storeUrl)
{
    return set(Url(storeUrl));
}

bool BlobStore::set(const Url &storeUrl)
{
    bool result = storeUrl.isValid();
    mUrl.clear();
    if (result)
    {
        mUrl = storeUrl;
        setObjectName("BlobStore:" + mUrl.toString());
    }
    return result;
}

bool BlobStore::connect()
{
    bool result = mUrl.isValid();
    if (result)
    {
        switch (mUrl.type())
        {
        case UrlType::Files:    result &= connectFiles();      break;
        case UrlType::SQLite:   result &= connectSqlLite();    break;
        case UrlType::PgSQL:    result &= connectPgSql();      break;
        default:            result = false;             break;
        }
    }
    return result;
}

bool BlobStore::create(const bool force)
{
    return false;
}

bool BlobStore::connectFiles()
{
    bool result = false;
    AbstractBlobBase * pBB = new BlobBaseFile(mUrl, this);
    if (pBB)
    {
        mpBlobBase = pBB;
        result = true;
    }
    return result;
}

bool BlobStore::connectSqlLite()
{
    bool result = false;
    AbstractBlobBase * pBB = new BlobBaseSqlLite(mUrl, this);
    if (pBB)
    {
        mpBlobBase = pBB;
        result = true;
    }

    return result;
}

bool BlobStore::connectPgSql()
{
    bool result = false;
    AbstractBlobBase * pBB = new BlobBasePgSql(mUrl, this);
    if (pBB)
    {
        mpBlobBase = pBB;
        result = true;
    }

    return result;
}
