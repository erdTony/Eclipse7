#pragma once

#include <QUrl>

#include <QUrlQuery>

#include <AText.h>

class Url : public QUrl
{
public: // typedef
    enum Type
    {
        $null = 0,
        Files,
        Dir,
        Http,
        Https,
        SqlLite,
        MySql,
        MariaDB,

        $error
    };

public: // ctors
    Url();
    Url(const QString &url, ParsingMode mode = TolerantMode);
    Url(const QUrl &other) noexcept;



public: // const
    Type type() const;
    QString string(const bool encoded=false) const;

public: // non-const
    void set(const QString &url, ParsingMode mode);
    void setScheme(const AText &scheme);
    void type(const AText &scheme);

public: //

private:
    Type mType=$null;
    QUrlQuery mQuery;
};

inline Url::Type Url::type() const { return mType; }
