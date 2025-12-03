#pragma once
#include "eirStore.h"

#include <QObject>

#include <Uid.h>
#include <Url.h>

#include "BlobItem.h"
class AbstractBlobBase;

class EIRSTORE_EXPORT BlobStore : public QObject
{
    Q_OBJECT
public: // ctors
    explicit BlobStore(QObject *parent = nullptr);
    explicit BlobStore(const QString &storeUrl, QObject *parent=nullptr);


public slots:

signals:

public: // const
    Url url() const;
    Url::Type type() const;

public: // non-const
    bool set(const QString &storeUrl);
    bool set(const Url &storeUrl);
    bool connect();
    bool create(const bool force=false);
    bool open();
    bool contains(const Uid &uid);
    BlobItem read(const Uid &uid);
    bool write(const Uid &uid, const BlobItem &item);

public: // pointers

private:
    bool connectFiles();
    bool connectSqlLite();
    bool connectPgSql();


private:
    Url mUrl;
    AbstractBlobBase * mpBlobBase=nullptr;
};

inline Url BlobStore::url() const { return mUrl; }
inline Url::Type BlobStore::type() const { return url().type(); }
