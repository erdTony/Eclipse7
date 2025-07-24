#include "Url.h"

#include <QDir>
#include <QMetaProperty>

#include <ObjectHelper.h>

Url::Url() {;}
Url::Url(const QString &url, QUrl::ParsingMode mode) { set(url, mode); }
Url::Url(const QUrl &other) noexcept { set(other.toString()); }
Url &Url::operator =(const QString &url) { set(url); return it(); }

QString Url::string(const bool encoded) const
{
    QUrl tUrl = mUrl;
    tUrl.setQuery(mQuery);
    return encoded ? tUrl.toEncoded() : tUrl.toString();
}

QDir Url::dir() const
{
    return QDir(mUrl.path());
}

void Url::set(const QString &url, QUrl::ParsingMode mode)
{
    mUrl.setUrl(url, mode);
    mQuery.setQuery(mUrl.query());
    mUrl.setQuery("");
    type(mUrl.scheme());
}

void Url::set(const QDir &dir)
{
    mUrl.setPath(dir.path());
}

void Url::setScheme(const CText &scheme)
{
    type(scheme);
    mUrl.setScheme(scheme);
}

void Url::type(const CText &scheme)
{
    Q_UNUSED(scheme);
    // TODO Url::type(const CText &scheme)
}



