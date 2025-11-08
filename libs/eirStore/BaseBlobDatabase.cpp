#include "BaseBlobDatabase.h"

BaseBlobDatabase::BaseBlobDatabase(const Url storeUrl, QObject *parent)
    : QObject{parent}
{
    setObjectName("BaseBlobDatabase");
}
