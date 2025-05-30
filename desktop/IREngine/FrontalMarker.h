#pragma once

#include <QObject>
#include "BaseObjdetMarker.h"

class FrontalMarker : public BaseObjdetMarker
{
    Q_OBJECT
public:
    explicit FrontalMarker(QObject *parent = nullptr);


public slots:
    virtual void reset() {;}

};
