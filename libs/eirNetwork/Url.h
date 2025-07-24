#pragma once
#include "eirNetwork.h"

#include <QObject>

#include <QUrl>
#include <QUrlQuery>
class QDir;

#include "CText.h"

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
        MySql,
        MariaDB,

        $error
    };

    typedef QList<Type> TypeList;

public: // ctors
    Url();
    Url(const QString &url, QUrl::ParsingMode mode=QUrl::TolerantMode);
    Url(const QUrl &other) noexcept;
    Url & operator = (const QString &url);


public: // const
    Type type() const;
    QString string(const bool encoded=false) const;
    QDir dir() const;

public: // non-const
    void set(const QString &url, QUrl::ParsingMode mode=QUrl::TolerantMode);
    void set(const QDir &dir);
    void setScheme(const CText &scheme);
    void type(const CText &scheme);

public: //

private:
    Url it() const;
    Url & it();

private:
    Type mType=$null;
    QUrl mUrl;
    QUrlQuery mQuery;
};

inline Url Url::it() const { return *this; }
inline Url &Url::it() { return *this; }
inline Url::Type Url::type() const { return mType; }
