#include "BlobStore.h"

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
        setObjectName("BlobStore:" + mUrl.string());
    }
    return result;
}

bool BlobStore::open()
{
    bool result = mUrl.isValid();
    if (result)
    {
        switch (mUrl.type())
        {
        case Url::Files:    result &= openFiles();      break;
        case Url::SqlLite:  result &= openSqlLite();    break;
        case Url::PgSql:    result &= openPgSql();      break;
        default:            result = false;             break;
        }
    }
    return result;
}

bool BlobStore::openFiles()
{
    bool result = false;
    AbstractBlobBase * pDB = new BlobBaseFile(mUrl, this);
    return result;
}

bool BlobStore::openSqlLite()
{
    bool result = false;

    return result;
}

bool BlobStore::openPgSql()
{
    bool result = false;

    return result;
}
