#pragma once

#include <Url.h>

class StoreUrl : public Url
{
public:
    StoreUrl();
    StoreUrl(const QString &url, QUrl::ParsingMode mode=QUrl::TolerantMode);
};
