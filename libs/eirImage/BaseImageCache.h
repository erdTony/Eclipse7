#pragma once

#include <QObject>

class BaseImageCache : public QObject
{
    Q_OBJECT
public:
    explicit BaseImageCache(QObject *parent = nullptr);

signals:
};
