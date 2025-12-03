#include "AbstractBlobBase.h"

AbstractBlobBase::AbstractBlobBase(const Url &storeUrl, QObject *parent)
    : QObject{parent}
    , mUrl(storeUrl)
{
    setObjectName("AbstractBlobDatabase:" + mUrl.toString());
}
