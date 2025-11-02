#pragma once

#include <QObject>

#include "StoreUrl.h"

class BlobStore : public QObject
{
    Q_OBJECT
public: // ctors
    explicit BlobStore(QObject *parent = nullptr);
    explicit BlobStore(const QString &url, QObject *parent=nullptr);


public slots:

signals:

public: // const

public: // non-const
    bool set(const QString &url);
    bool set(const StoreUrl &url);
    bool open();

public: // pointers

private:
    StoreUrl mUrl;

};
