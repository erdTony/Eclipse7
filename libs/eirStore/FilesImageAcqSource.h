#pragma once

#include <QObject>
#include "BaseImageAcqSource.h"

class FilesImageAcqSource : public BaseImageAcqSource
{
    Q_OBJECT
public:
    explicit FilesImageAcqSource(QObject *parent = nullptr);

signals:
};
