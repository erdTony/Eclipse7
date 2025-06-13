#pragma once

#include <QObject>

#include <Key.h>
#include <KeyMap.h>

#include "ImageAcqConfig.h"

class ImageAcqManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageAcqManager(QObject *parent = nullptr);

public:

signals:

public:


public:


private:
    KeyMapT<KeySeg, ImageAcqConfig> mSourceConfigMap;
};
