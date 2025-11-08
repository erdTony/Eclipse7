#pragma once
#include "eirNetwork.h"

#include <QObject>

#include <QUrl>
#include <QUrlQuery>
class QDir;

#include <AText.h>
#include <ATextList.h>

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
        SqlLite,
        PGSQL,
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
    Type type() const;
    QString string(const bool encoded=false) const;
    QDir dir() const;
    bool contains(const AText &queryName) const;
    AText value(const AText &queryName) const;
    AText operator [] (const AText &queryName) const;

public: // non-const
    void clear();
    void set(const QString &url, QUrl::ParsingMode mode=QUrl::TolerantMode);
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
};

inline AText Url::operator [](const AText &queryName) const { return value(queryName); }
inline Url Url::it() const { return *this; }
inline Url &Url::it() { return *this; }
inline Url::Type Url::type() const { return mType; }
