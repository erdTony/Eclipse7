#include "AbstractBlobDatabase.h"

AbstractBlobDatabase::AbstractBlobDatabase(const Url &storeUrl, QObject *parent)
    : QObject{parent}
    , mUrl(storeUrl)
{
    setObjectName("AbstractBlobDatabase:" + mUrl.string());
}
