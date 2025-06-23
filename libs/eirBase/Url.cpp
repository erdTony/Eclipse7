#include "Url.h"

#include <QMetaProperty>

#include <ObjectHelper.h>

Url::Url() {;}
Url::Url(const QString &url, QUrl::ParsingMode mode) { set(url, mode); }
Url::Url(const QUrl &other) noexcept { set(other.toString()); }

void Url::set(const QString &url, QUrl::ParsingMode mode)
{
    mUrl.setUrl(url, mode);
    mQuery.setQuery(mUrl.query());
    mUrl.setQuery("");
    type(mUrl.scheme());
}

void Url::setScheme(const CText &scheme)
{
    type(scheme);
    mUrl.setScheme(scheme);
}

void Url::type(const CText &scheme)
{
    // TODO
}



