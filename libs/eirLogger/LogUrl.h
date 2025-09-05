#pragma once
#include "eirLogger.h"

#include <QUrl>
#include <QUrlQuery>

#include <CText.h>

#include "LogFile.h"
#include "LogFilter.h"
#include "LogFormat.h"

class EIRLOGGER_EXPORT LogUrl
{
public: // types
    enum Scheme
    {
        $null = 0,
        LogOut,
    };

public: // ctors
    LogUrl();
    LogUrl(const Scheme s, const QString &u);

public: // const
    LogFormat format() const;
    QString toString() const;
    CText toCText() const;
    operator QString () const;
    operator CText () const;

public: // non-const
    void set(const Scheme s, QString u);
    LogFile & file();

private: // non-const
    void setLogOut(const QString &u);
    void setLogErr(const QString &u);
    void setFileInfo();
    void setFilter();
    void setFormat();


private:
    Scheme mScheme=$null;
    QUrl mUrl;
    QUrlQuery mQuery;
    LogFile mLogFile;
    LogFilter mFilter;
    LogFormat mFormat;

};

inline LogFormat LogUrl::format() const { return mFormat; }
inline CText LogUrl::toCText() const { return CText(toString()); }
inline LogUrl::operator QString() const { return toString(); }
inline LogUrl::operator CText() const { return toCText(); }
inline LogFile &LogUrl::file() { return mLogFile; }
