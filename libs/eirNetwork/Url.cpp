#include "Url.h"

Url::Url() {}

Url::Url(const QString &url, ParsingMode mode) { set(url, mode); }
Url::Url(const QUrl &other) noexcept : QUrl(other) {;}

void Url::set(const QString &url, ParsingMode mode)
{
    type(scheme());
    QUrl::setUrl(url, mode);
    mQuery.setQuery(QUrl::query());
    QUrl::setQuery("");
}

void Url::setScheme(const AText &scheme)
{
    type(scheme);
    QUrl::setScheme(scheme);
}

void Url::type(const AText &scheme)
{
    Type result = $error;
    if (scheme.isEmpty())               result = $null;
    else if ("files" == scheme)         result = Files;
    else if ("dir" == scheme)           result = Dir;

    else if ("sqllite" == scheme)       result = SqlLite;

    else                                return;
    mType = result;
}



