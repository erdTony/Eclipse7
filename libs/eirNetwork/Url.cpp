#include "Url.h"

#include <QDir>
#include <QMetaProperty>

#include <ObjectHelper.h>

Url::Url() {;}
Url::Url(const QString &url, QUrl::ParsingMode mode) { set(url, mode); }
Url::Url(const QUrl &other) noexcept { set(other.toString()); }

Url &Url::operator =(const QString &url) { set(url); return it(); }

bool Url::isNull() const
{
    return mUrl.isEmpty() || $null == type();
}

bool Url::isValid() const
{
    return mUrl.isValid() && $null != type() && $other != type();
}

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

void Url::clear()
{
    mType = $null, mUrl.clear(), mQuery.clear(), mQueryText.clear(),
        mQueryList.clear(), mQueryPairs.clear(), mQueryPairMap.clear();
}

void Url::set(const QString &url, QUrl::ParsingMode mode)
{
    clear();
    mUrl.setUrl(url, mode);
    mQuery.setQuery(mUrl.query());
    mUrl.setQuery("");
    type(mUrl.scheme());
    mQueryText = mQuery.toString();
    if ( ! mQueryText.isEmpty())
    {
        mQueryList = mQueryText.split('&');
        mQueryPairs = mQueryList.split('=');
        foreach (const AText::Pair cPair,  mQueryPairs)
        {
            const AText cName = cPair.first;
            const AText cValue = cPair.second;
            mQueryPairMap.insert(cName, cValue);
        }
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
    const AText cAtx = scheme.toLower();
    if (scheme.isEmpty())           result = $null;
    else if ("troll" == scheme)     result = Troll;
    else if ("stdio" == scheme)     result = Stdio;
    else if ("textFile" == scheme)  result = TextFile;
    else if ("files" == scheme)     result = Files;
    else if ("dir" == scheme)       result = Dir;
    else if ("http" == scheme)      result = Http;
    else if ("https" == scheme)     result = Https;
    else if ("qqlLite" == scheme)   result = SqlLite;
    return mType = result;
}



