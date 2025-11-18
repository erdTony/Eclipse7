#pragma once
#include "eirStore.h"

#include "BlobItem.h"
#include <QObject>

#include <Url.h>
class Uid;

class EIRSTORE_EXPORT AbstractBlobBase : public QObject
{
    Q_OBJECT
public: // ctors
    explicit AbstractBlobBase(const Url &storeUrl,
                              QObject *parent = nullptr);

public slots:
    virtual bool open() = 0;
    virtual bool contains(const Uid &uid) = 0;
    virtual BlobItem read(const Uid &uid) = 0;
    virtual bool write(const Uid &uid, const BlobItem &item) = 0;

signals:

public: // const

public: // non-const





protected:
    Url mUrl;

};
