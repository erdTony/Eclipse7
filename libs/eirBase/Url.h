#pragma once
#include "eirBase.h"

#include <QObject>

#include <QUrl>
#include <QUrlQuery>

#include "CText.h"

class EIRBASE_EXPORT Url
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



public: // const
    Type type() const;
    QString string(const bool encoded=false) const;

public: // non-const
    void set(const QString &url, QUrl::ParsingMode mode=QUrl::TolerantMode);
    void setScheme(const CText &scheme);
    void type(const CText &scheme);

public: //

private:
    Type mType=$null;
    QUrl mUrl;
    QUrlQuery mQuery;
};

inline Url::Type Url::type() const { return mType; }
