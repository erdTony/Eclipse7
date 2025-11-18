#pragma once
#include "eirStore.h"

#include <QByteArray>

#include <AText.h>
#include <Key.h>
#include <KeyMap.h>
#include <Uid.h>

class EIRSTORE_EXPORT BlobItem
{
public:
    BlobItem(const bool nullUid=true);
    BlobItem(const Uid &uid);
    BlobItem(const Uid::Version ver);
    BlobItem(const Uid &uid, const QByteArray &ba);
    BlobItem(const Uid &uid, const KeyTextMap &map, const QByteArray &ba);

public: // const
    bool isEmpty() const;
    Uid uid() const;
    bool isNull() const;
    KeyTextMap map() const;
    bool contains(const Key &key) const;
    AText map(const Key &key) const;
    QByteArray bytes() const;

public: // non-const
    void uid(const Uid &u);
    void map(const KeyTextMap &m);
    void map(const Key &key, const AText &txt);
    void bytes(const QByteArray &ba);
    void clear();

private:
    Uid mUid;
    KeyTextMap mMap;
    QByteArray mBytes;
};

inline Uid BlobItem::uid() const { return mUid; }
inline bool BlobItem::isNull() const { return mUid.isNull(); }
inline KeyTextMap BlobItem::map() const { return mMap; }
inline bool BlobItem::contains(const Key &key) const { return mMap.contains(key); }
inline QByteArray BlobItem::bytes() const { return mBytes; }
inline void BlobItem::uid(const Uid &u) { mUid = u; }
inline void BlobItem::map(const KeyTextMap &m) { mMap = m; }
inline void BlobItem::bytes(const QByteArray &ba) { mBytes = ba; }
