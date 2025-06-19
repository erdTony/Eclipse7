#pragma once

#include <QObject>

class BaseLogOutput : public QObject
{
    Q_OBJECT
protected:
    explicit BaseLogOutput(QObject *parent = nullptr);

signals:
};
