#pragma once
#include "eirStore.h"

#include <QObject>

#include <Url.h>

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

public: // non-const
    bool set(const QString &storeUrl);
    bool set(const Url &storeUrl);
    bool open();



public: // pointers

private:
    bool openFiles();
    bool openSqlLite();
    bool openPgSql();


private:
    Url mUrl;
    AbstractBlobBase * mpDatabase=nullptr;
};
