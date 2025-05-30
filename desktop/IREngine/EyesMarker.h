#pragma once

#include <QObject>
#include "BaseObjdetMarker.h"

class EyesMarker : public BaseObjdetMarker
{
    Q_OBJECT
public:
    explicit EyesMarker(QObject *parent = nullptr);
};
