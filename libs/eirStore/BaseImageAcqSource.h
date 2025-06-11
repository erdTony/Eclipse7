#pragma once

#include <QObject>

#include <Url.h>

class BaseImageAcqSource : public QObject
{
    Q_OBJECT
public:
    explicit BaseImageAcqSource(QObject *parent = nullptr);
protected:
    BaseImageAcqSource(const Url &Url, QObject *parent = nullptr);

signals:
};
