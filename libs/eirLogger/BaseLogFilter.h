#pragma once
#include "eirLogger.h"

#include <QObject>

class BaseLogFilterItem;

class EIRLOGGER_EXPORT BaseLogFilter : public QObject
{
    Q_OBJECT
public:
    explicit BaseLogFilter(QObject *parent = nullptr);
    void add(const BaseLogFilterItem &lfi);

signals:
};
