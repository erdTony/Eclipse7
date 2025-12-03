#pragma once
#include "eirNetwork.h"

#include <QObject>

#include <QDir>
#include <QFileInfo>
#include <QUrl>
#include <QUrlQuery>

#include <AText.h>
#include <ATextList.h>
#include <Types.h>

class EIRNETWORK_EXPORT Url
{
    Q_GADGET
public: // types
    enum Type
    {
        $null = 0,
        Troll,
        Stdio,
        TextFile,
        Files,
        Dir,
        Http,
        Https,
        SQLite,
        PgSql,
        $other
    };

    typedef QList<Type> TypeList;

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
    Type type() const;
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
    QFileInfo localFlle() const;
    QDir localDir() const;
    bool contains(const AText &queryName) const;
    AText value(const AText &queryName) const;
    AText operator [] (const AText &queryName) const;

public: // non-const
    void clear();
    void set(const QString &s, QUrl::ParsingMode mode=QUrl::TolerantMode);
    void dir(const QDir &dir);
    void setScheme(const AText &scheme);
    Type type(const AText &scheme);

public: //

private:
    Url it() const;
    Url & it();

private:
    Type mType=$null;
    QUrl mUrl;
    QUrlQuery mQuery;
    AText mQueryText;
    ATextList mQueryList;
    ATextList::PairList mQueryPairs;
    ATextList::PairMap mQueryPairMap;
    QFileInfo mLocalFile;
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

inline AText Url::scheme() const { return mScheme; }
inline AText Url::operator [](const AText &queryName) const { return value(queryName); }
inline Url Url::it() const { return *this; }
inline Url &Url::it() { return *this; }
inline Url::Type Url::type() const { return mType; }
