#pragma once
#include "eirStore.h"

#include <QObject>

#include <Key.h>
#include <KeyMap.h>

#include "ImageAcqConfig.h"

class EIRSTORE_EXPORT ImageAcqManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageAcqManager(QObject *parent = nullptr);

public:

signals:

public:


public:


private:
    KeyMapT<ImageAcqConfig> mSourceConfigMap;
};
