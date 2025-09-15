#pragma once

#include <QObject>

class EfpImageReader : public QObject
{
    Q_OBJECT
public:
    explicit EfpImageReader(QObject *parent = nullptr);

signals:
};
