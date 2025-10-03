#pragma once

#include "BaseImageCache.h"

class MemoryImageCache : public BaseImageCache
{
    Q_OBJECT
public:
    explicit MemoryImageCache(QObject *parent = nullptr);
};
