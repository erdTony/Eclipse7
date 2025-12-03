#pragma once

#include <Url.h>

class BlobStoreUrl : public Url
{
public:
    BlobStoreUrl(const Url &url);
};
