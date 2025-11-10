#pragma once

#include "AbstractBlobDatabase.h"

class BlobPgSqlDatabase : public AbstractBlobDatabase
{
    Q_OBJECT
public:
    explicit BlobPgSqlDatabase(const Url &storeUrl, QObject *parent = nullptr);

    // AbstractBlobDatabase interface
public slots:
    virtual bool open() override;
    virtual bool contains(const Uid &uid) override;
    virtual BlobItem read(const Uid &uid) override;
    virtual bool write(const Uid &uid, const BlobItem &item) override;
};
