#include "BlobStore.h"

BlobStore::BlobStore(QObject *parent)
    : QObject{parent}
{
    setObjectName("BlobStore");
}

BlobStore::BlobStore(const QString &url, QObject *parent)
    : QObject{parent}
{
    set(url);
}

bool BlobStore::set(const QString &url)
{
    return set(StoreUrl(url));
}

bool BlobStore::set(const StoreUrl &url)
{
    bool result = url.isValid();
    mUrl.clear();
    if (result)
    {
        mUrl = url;
        setObjectName("BlobStore:" + mUrl.string());
    }
    return result;
}

bool BlobStore::open()
{
    bool result = true;

    return result;
}
