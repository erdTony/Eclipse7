#pragma once
#include "eirStore.h"

#include "AbstractBlobBase.h"

class EIRSTORE_EXPORT BlobBaseFile : public AbstractBlobBase
{
    Q_OBJECT
public:
    explicit BlobBaseFile(const Url storeUrl, QObject *parent = nullptr);

    // AbstractBlobDatabase interface
public slots:
    virtual bool open() override;
    virtual bool contains(const Uid &uid) override;
    virtual BlobItem read(const Uid &uid) override;
    virtual bool write(const Uid &uid, const BlobItem &item) override;
};
