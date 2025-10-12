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

bool Url::contains(const AText &queryName) const
{
    return mQueryPairMap.contains(queryName);
}

AText Url::value(const AText &queryName) const
{
    return mQueryPairMap.value(queryName);
}

void Url::set(const QString &url, QUrl::ParsingMode mode)
{
    mUrl.setUrl(url, mode);
    mQuery.setQuery(mUrl.query());
    mUrl.setQuery("");
    type(mUrl.scheme());
    mQueryText = mQuery.toString();
    mQueryList = mQueryText.split('&');
    mQueryPairs = mQueryList.split('=');
    foreach (const AText::Pair cPair,  mQueryPairs)
    {
        const AText cName = cPair.first;
        const AText cValue = cPair.second;
        mQueryPairMap.insert(cName, cValue);
    }
}

void Url::dir(const QDir &dir)
{
    mUrl.setPath(dir.path());
}

void Url::setScheme(const AText &scheme)
{
    type(scheme);
    mUrl.setScheme(scheme);
}

Url::Type Url::type(const AText &scheme)
{
    Url::Type result=$other;
    if (scheme.isEmpty())           result = $null;
    else if ("Troll" == scheme)     result = Troll;
    else if ("Stdio" == scheme)     result = Stdio;
    else if ("TextFile" == scheme)  result = TextFile;
    else if ("Files" == scheme)     result = Files;
    else if ("Dir" == scheme)       result = Dir;
    else if ("Http" == scheme)      result = Http;
    else if ("Https" == scheme)     result = Https;
    else if ("SqlLite" == scheme)   result = SqlLite;
    else if ("MySql" == scheme)     result = MySql;
    else if ("MariaDB" == scheme)   result = MariaDB;
    return mType = result;
}



