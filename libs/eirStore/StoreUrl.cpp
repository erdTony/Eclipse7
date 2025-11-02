#include "StoreUrl.h"

StoreUrl::StoreUrl() {;}
StoreUrl::StoreUrl(const QString &url, QUrl::ParsingMode mode) : Url(url, mode) {;}

