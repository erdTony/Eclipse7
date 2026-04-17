#include "Url.h"

#include <QtDebug>
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
    qInfo() << Q_FUNC_INFO << mUrl.toString() << mUrl.isLocalFile() << mUrl.toLocalFile();
    bool result = false;
    QUrl tQUrl(mUrl);
    if (type().isFile()) tQUrl.setScheme("file");
    if (tQUrl.isLocalFile())
    {
        const QString cFileString =  tQUrl.toLocalFile();
        QFileInfo tFI(cFileString);
        result |= tFI.isFile() && tFI.exists();
    }
    qInfo() << result << tQUrl << tQUrl.isLocalFile() << tQUrl.toLocalFile();
    return result;
}

bool Url::isLocalDir() const
{
    bool result = false;
    qInfo() << Q_FUNC_INFO << mUrl.toString() << mUrl.isLocalFile() << mUrl.toLocalFile();
    if (isLocalFile())
    {
        const QString cFileString =  localFlleInfo().path();
        QFileInfo tFI(cFileString);
        if (tFI.isDir())
        {
            QDir tDir(cFileString);
            result |= tDir.isReadable();
        }
    }
    return result;
}

AText Url::authority() const
{
    return username() + ":" + password();
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
    return mQueryPairMMap.contains(queryName);
}

AText Url::value(const AText &queryName) const
{
    return mQueryPairMMap.value(queryName);
}

ATextList Url::queryMapList()
{
    return ATextList::toList(mQueryPairMMap);
}

void Url::clear()
{
    mType = UrlType::$null, mUrl.clear(), mQuery.clear(), mQueryText.clear(),
        mQueryList.clear(), mQueryPairs.clear(), mQueryPairMMap.clear();
}

void Url::set(const QString &s, QUrl::ParsingMode mode)
{
    qInfo() << Q_FUNC_INFO << s << mode;
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
            mQueryPairMMap.insert(cName, cValue);
        }
    }

    mString = s;
    mScheme = mUrl.scheme();
    type(scheme());
    if (type().isFile())
    {
        mUrl.setScheme(mScheme = "file");
        mLocalFileInfo = QFileInfo(mUrl.toLocalFile());
    }
    mUsername = mUrl.userName();
    mPassword = mUrl.password();
    mHost = mUrl.host();
    mPort = mUrl.port();
    mPath = mUrl.path();
    mPathList = mPath.split(QDir::separator().cell());
    qInfo() << Q_FUNC_INFO << string() << scheme() << type().name() << authority();
    qInfo() << path() << pathCount() << pathDir();
    qInfo() << localFlleInfo() << localDir() << queryMapList();
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

Url::List Url::list(const QString delimtedUrls, const QChar hinge)
{
    Url::List result;
    foreach (QString s, delimtedUrls.split(hinge))
    {
        Url tUrl(s);
        if (tUrl.isValid())
            result << tUrl;
    }
    return result;
}




