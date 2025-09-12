#pragma once
#include "eirGui.h"

#include <QObject>

class EIRGUI_EXPORT IconManager : public QObject
{
    Q_OBJECT
public:
    explicit IconManager(QObject *parent = nullptr);

signals:
};
