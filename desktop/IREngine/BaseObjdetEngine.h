#pragma once

#include <QObject>
#include "Objdet.h"

class BaseObjdetEngine : public Objdet
{
    Q_OBJECT
public: // ctors
    explicit BaseObjdetEngine(QObject *parent = nullptr);
protected:
    BaseObjdetEngine(const Objdet::Class objcls, QObject *parent = nullptr);

signals:

public: // static

private:
};
