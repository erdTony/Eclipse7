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
    return mUrl.isEmpty() || UrlType::$null == type();
}

bool Url::isValid() const
{
    return mUrl.isValid() && UrlType::$null != type() && UrlType::$other != type();
}

bool Url::isLocalFile() const
{
//    return mUrl.isLocalFile() || TextFile == type();
    bool result = false;
    if (mUrl.isLocalFile())
    {
        const QString cFileString =  mUrl.toLocalFile();
        QFileInfo tFI(cFileString);
        result = tFI.isFile() && tFI.exists();
    }
    return result;
}

bool Url::isLocalDir() const
{
    bool result = false;
    if (mUrl.isLocalFile())
    {
        const QString cFileString =  mUrl.toLocalFile();
        QFileInfo tFI(cFileString);
        if (tFI.isDir())
        {
            QDir tDir(cFileString);
            result = tDir.isReadable();
        }
    }
    return result;
}

QString Url::toString(const bool encoded) const
{
    QUrl tUrl = mUrl;
    tUrl.setQuery(mQuery);
    return encoded ? tUrl.toEncoded() : tUrl.toString();
}

QDir Url::pathDir() const
{
    return QDir(mUrl.path());
}

QDir Url::localDir() const
{
    QDir result;
    if (isLocalFile())
    {
        const QString cFileString =  mUrl.toLocalFile();
        QFileInfo tFI(cFileString);
        if (tFI.isDir())
            result = QDir(cFileString);
    }
    return result;
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
    mType = UrlType::$null, mUrl.clear(), mQuery.clear(), mQueryText.clear(),
        mQueryList.clear(), mQueryPairs.clear(), mQueryPairMap.clear();
}

void Url::set(const QString &s, QUrl::ParsingMode mode)
{
    clear();
    mUrl.setUrl(s, mode);
    mQuery.setQuery(mUrl.query());
    mUrl.setQuery("");

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

    mString = s;
    mScheme = mUrl.scheme();
    type(scheme());
    mUsername = mUrl.userName();
    mPassword = mUrl.password();
    mHost = mUrl.host();
    mPort = mUrl.port();
    mPath = mUrl.path();
    mPathList = mPath.split(QDir::separator().cell());
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

UrlType Url::type(const AText &scheme)
{
    UrlType result;
    result.set(scheme);
    return mType = result;
}




