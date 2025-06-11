#pragma once

#include <QObject>

class ImageAcqManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageAcqManager(QObject *parent = nullptr);

signals:
};
