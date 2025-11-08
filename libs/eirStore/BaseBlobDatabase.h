#pragma once

#include <QObject>

#include <Url.h>
class Uid;

class BaseBlobDatabase : public QObject
{
    Q_OBJECT
public: // ctors
    explicit BaseBlobDatabase(const Url storeUrl,
                              QObject *parent = nullptr);

public slots:
    virtual bool open() = 0;
    virtual bool contains(const Uid &uid) = 0;
    virtual QByteArray read(const Uid &uid) = 0;

signals:

public: // const

public: // non-const





private:
    Url mUrl;

};
