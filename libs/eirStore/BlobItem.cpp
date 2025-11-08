#include "BlobItem.h"

BlobItem::BlobItem(const bool nullUid) : mUid(nullUid ? Uid() : Uid(Uid::VerRandom)) {;}
BlobItem::BlobItem(const Uid &uid) : mUid(uid) {;}
BlobItem::BlobItem(const Uid::Version ver) : mUid(ver) {;}
BlobItem::BlobItem(const Uid &uid, const QByteArray &ba) : mUid(uid), mBytes(ba) {;}
BlobItem::BlobItem(const Uid &uid, const KeyTextMap &map, const QByteArray &ba) : mUid(uid), mMap(map), mBytes(ba) {;}

bool BlobItem::isEmpty() const
{
    return mUid.isNull() && mMap.isEmpty() && mBytes.isEmpty();
}

void BlobItem::clear()
{
    mUid.nullify(), mMap.clear(), mBytes.clear();
}



