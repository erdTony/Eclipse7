#pragma once

#include "AbstractBlobDatabase.h"

class BlobFileDatabase : public AbstractBlobDatabase
{
    Q_OBJECT
public:
    explicit BlobFileDatabase(const Url storeUrl, QObject *parent = nullptr);

    // AbstractBlobDatabase interface
public slots:
    virtual bool open() override;
    virtual bool contains(const Uid &uid) override;
    virtual BlobItem read(const Uid &uid) override;
    virtual bool write(const Uid &uid, const BlobItem &item) override;
};
