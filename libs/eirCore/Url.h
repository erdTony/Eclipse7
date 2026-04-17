#pragma once
#include "eirCore.h"

#include <QObject>

#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QUrl>
#include <QUrlQuery>

#include <AText.h>
#include <ATextList.h>
#include <Types.h>

#include "UrlType.h"

class EIRCORE_EXPORT Url
{
    Q_GADGET
public: // types
    typedef QList<Url> List;

public: // ctors
    Url();
    Url(const QString &url, QUrl::ParsingMode mode=QUrl::TolerantMode);
    Url(const QUrl &other) noexcept;
    Url & operator = (const QString &url);


public: // const
    bool isNull() const;
    bool isValid() const;
    bool isLocalFile() const;
    bool isLocalDir() const;
    AText string() const;
    AText scheme() const;
    UrlType type() const;
    AText username() const;
    AText password() const;
    AText userinfo() const;
    AText host() const;
    WORD port() const;
    AText authority() const;
    AText path() const;
    AText path(const Index ix) const;
    Count pathCount() const;
    QString toString(const bool encoded=false) const;
    QDir pathDir() const;
    QFileInfo localFlleInfo() const;
    QDir localDir() const;
    bool contains(const AText &queryName) const;
    AText value(const AText &queryName) const;
    AText operator [] (const AText &queryName) const;
    ATextList queryMapList();

public: // non-const
    void clear();
    void set(const QString &s, QUrl::ParsingMode mode=QUrl::TolerantMode);
    void dir(const QDir &dir);
    void setScheme(const AText &scheme);
    UrlType type(const AText &scheme);

public: // static
    List list(const QString delimtedUrls, const QChar hinge=QChar(';'));

private:
    Url it() const;
    Url & it();

private:
    UrlType mType=UrlType::$null;
    QUrl mUrl;
    QUrlQuery mQuery;
    AText mQueryText;
    ATextList mQueryList;
    ATextList::PairList mQueryPairs;
    ATextList::PairMMap mQueryPairMMap;
    QFileInfo mLocalFileInfo;
    QDir mLocalDir;

    AText mString;
    AText mScheme;
    AText mUsername;
    AText mPassword;
    AText mHost;
    WORD mPort;
    AText mPath;
    ATextList mPathList;
};

inline AText Url::string() const { return mString; }
inline AText Url::scheme() const { return mScheme; }
inline AText Url::operator [](const AText &queryName) const { return value(queryName); }
inline Url Url::it() const { return *this; }
inline Url &Url::it() { return *this; }
inline UrlType Url::type() const { return mType; }
inline AText Url::username() const  { return mUsername; }
inline AText Url::password() const  { return mPassword; }
inline AText Url::path() const  { return mPath; }
inline Count Url::pathCount() const  { return mPathList.count(); }
inline QFileInfo Url::localFlleInfo() const  { return mLocalFileInfo; }


