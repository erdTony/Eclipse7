#pragma once

#include <QObject>
#include "BaseObjdetEngine.h"

class FrontalObjdet : public BaseObjdetEngine
{
    Q_OBJECT
public:
    explicit FrontalObjdet(QObject *parent = nullptr);

signals:
};
