#pragma once

#include <QSharedDataPointer>

#include <QString>
#include <QVersionNumber>

class QCoreApplication;


class VersionInfoData;

class VersionInfo
{
public: // types
    struct WindowsVersion   { qint16     word[4]; };
    struct LinuxVersion     { unsigned      uint[3]; };
    enum StringOption
    {
        $null                   = 0,
        Dotted                  = 0x00000001,
        WithLowerVDot           = 0x00000002,
        WithDotted              = 0x01000000,
        WithDWord               = 0x02000000,
        WithQWord               = 0x04000000,
        WithBranchName          = 0x08000000,
        WithoutFinal            = 0x20000000,
        WithoutReleaseNumber    = 0x40000000,
        WithoutBranch           = 0x80000000,
    };
    Q_DECLARE_FLAGS(StringOptions, StringOption);
    Q_FLAGS(StringOptions);

public: // ctors
    VersionInfo(const quint8 maj, const quint16 min, const quint8 rls,
                const quint16 bch, const quint16 bld, const char * bnm,
                const char * app, const char * org, const char * desc);

public: // const
    quint8 major() const;
    quint16 majmin() const;       // 0..31 0..999
    quint16 minor() const;        // 0..999
    quint8 release() const;      // _A..Z,AA..WW,X0..9A..X,0xA?,0xB?,0xC?,0xF?
    quint16 branch() const;       // 0001..4999 Issue, 5001..5999 Customer
    quint16 build() const;        // ++at Develop,Current,Release,Main
    QString branchname() const;
    QString appname() const;
    QString appdesc() const;
    QString orgname() const;
    QString product() const;
    QString company() const;
    QString copyright() const;
    QString legal() const;
    QVersionNumber  qtVersion() const;
    WindowsVersion  windowsVersion() const;
    LinuxVersion    linuxVersion() const;
    bool isNull() const;
    QString toString(const StringOptions opts=$null) const;
    quint32 toDWord() const;
    quint64 toQWord() const;
    bool updateApp(QCoreApplication * pCoreApp) const;


public: // non-const
    void clear();
    void set(const VersionInfo &vi);
    void set(const quint8 maj, const quint16 min, const quint8 rls,
             const quint16 bch, const quint16 bld, const char * bnm,
             const char * app, const char * org,
             const char * desc);
    void company(const QString &co);
    void copyright(const QString &co);
    void legal(const QString &leg);
    void product(const QString &prod);

private:
    QString dottedString() const;
    QString releaseString(const StringOptions opts) const;
    QString namedRelease(const char * name, const StringOptions opts) const;
    void setQt();
    void setWindows();


public: // builtin
    VersionInfo();
    VersionInfo(const VersionInfo &);
    VersionInfo &operator=(const VersionInfo &);
    ~VersionInfo();

private:
    QSharedDataPointer<VersionInfoData> data;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(VersionInfo::StringOptions)

