#include "VersionInfo.h"

#include <QCoreApplication>

class VersionInfoData : public QSharedData
{
public:
    quint8            d_major;        // 0..99
    quint16            d_minor;        // 0..999
    quint8            d_release;      // _A..Z,AA..WW,X0..9A..X,0xA?,0xB?,0xC?,0xF?
    quint16            d_branch;       // 0001..4999 Issue, 5001..5999 Customer
    quint16            d_build;        // ++at Develop,Current,Release,Main
    QString           d_branchname;
    QString           d_appname;
    QString           d_appdesc;
    QString           d_orgname;
    QString           d_product;
    QString           d_company;
    QString           d_copyright;
    QString           d_legal;
    QVersionNumber  d_qtVersion;
    VersionInfo::WindowsVersion  d_windowsVersion;
    VersionInfo::LinuxVersion    d_linuxVersion;
};

VersionInfo::VersionInfo(const quint8 maj, const quint16 min,
            const quint8 rls, const quint16 bch, const quint16 bld,
            const char *bnm, const char *app,
            const char *org, const char *desc)
: data(new VersionInfoData)
{
    set(maj, min, rls, bch, bld, bnm, app, org, desc);
}

quint8 VersionInfo::major() const
{
    return data->d_major;
}

quint16 VersionInfo::majmin() const
{
    return major() * 1000U + minor();
}

quint16 VersionInfo::minor() const
{
    return data->d_minor;
}

quint8 VersionInfo::release() const
{
    return data->d_release;
}

quint16 VersionInfo::branch() const
{
    return data->d_branch;
}

quint16 VersionInfo::build() const
{
    return data->d_build;
}

QString VersionInfo::branchname() const
{
    return data->d_branchname;
}

QString VersionInfo::appname() const
{
    return data->d_appname;
}

QString VersionInfo::appdesc() const
{
    return data->d_appdesc;
}

QString VersionInfo::orgname() const
{
    return data->d_orgname;
}

QString VersionInfo::product() const
{
    return data->d_product;
}

QString VersionInfo::company() const
{
    return data->d_company;
}

QString VersionInfo::copyright() const
{
    return data->d_copyright;
}

QString VersionInfo::legal() const
{
    return data->d_legal;
}


QVersionNumber VersionInfo::qtVersion() const
{
    return data->d_qtVersion;
}

VersionInfo::WindowsVersion VersionInfo::windowsVersion() const
{
    return data->d_windowsVersion;
}

VersionInfo::LinuxVersion VersionInfo::linuxVersion() const
{
    return data->d_linuxVersion;
}


bool VersionInfo::isNull() const
{
    return 0 == major() && 0 == minor();
}

QString VersionInfo::toString(const StringOptions opts) const
{
    QString result;
    if (opts.testFlag(Dotted))
    {
        result = dottedString();
    }
    else
    {
        result = QString("%1%2.%3%4")
                     .arg(opts.testFlag(WithLowerVDot) ? "v." : "")
                     .arg(major())
                     .arg(minor(), 2, 10, QChar('0'))
                     .arg(releaseString(opts));
        if (branch() && ! opts.testFlag(WithoutBranch))
        {
            result += QString("+%1").arg(branch(), 5, 10, QChar('0'));
            if (opts.testFlag(WithBranchName))
                result += "-" + branchname();
        }
    }
    if (opts.testFlag(WithDotted))
        result += QString(" [%1]").arg(dottedString());
    if (opts.testFlag(WithDWord))
        result += QString(" [%1]").arg(toDWord(),  8, 16, QChar('0'));
    if (opts.testFlag(WithQWord))
        result += QString(" [%1]").arg(toQWord(), 16, 16, QChar('0'));
    return result;}

quint32 VersionInfo::toDWord() const
{
    static union
    {
        quint32       uDWord;
        struct
        {
            quint8    sMajor;
            quint16    sMinor;
            quint8    sRelease;
        };
    } stUnion;
    stUnion.sMajor = major(), stUnion.sMinor = minor(), stUnion.sRelease = release();
    return stUnion.uDWord;
}

quint64 VersionInfo::toQWord() const
{
    static union
    {
        quint64       uQWord;
        struct
        {
            quint32   sMajMin;
            quint32   sRelease;
            quint32   sBranch;
            quint32   sBuild;
        };
    } stUnion;
    stUnion.sMajMin = major() * 1000 + minor(), stUnion.sRelease = release();
    stUnion.sBranch = branch(), stUnion.sBuild = build();
    return stUnion.uQWord;
}

bool VersionInfo::updateApp(QCoreApplication *pCoreApp) const
{
    pCoreApp->setApplicationName(appname());
    pCoreApp->setApplicationVersion(toString());
    pCoreApp->setOrganizationName(orgname());
    return true;
}

void VersionInfo::clear()
{
    data->d_major = data->d_minor = data->d_release = data->d_branch = data->d_build = 0;
    data->d_branchname.clear(), data->d_appname.clear(), data->d_orgname.clear(),
    data->d_company.clear(), data->d_copyright.clear(), data->d_legal.clear();
    data->d_qtVersion = QVersionNumber();
    data->d_windowsVersion = WindowsVersion{0,0,0,0};
    data->d_linuxVersion = LinuxVersion{0,0,0};
}

void VersionInfo::set(const VersionInfo &vi)
{
    set(vi.major(), vi.minor(), vi.release(), vi.branch(), vi.build(),
        qPrintable(vi.branchname()),
        qPrintable(vi.appname()),
        qPrintable(vi.orgname()),
        qPrintable(vi.appdesc()));
    data->d_product = vi.product(), data->d_company = vi.company();
    data->d_copyright = vi.copyright(), data->d_legal = vi.legal();
    data->d_linuxVersion = vi.data->d_linuxVersion;
    setQt();
    setWindows();
}

void VersionInfo::set(const quint8 maj, const quint16 min,
        const quint8 rls, const quint16 bch, const quint16 bld,
        const char *bnm, const char *app,
        const char *org, const char *desc)
{
    data->d_major = maj, data->d_minor = min, data->d_release = rls,
        data->d_branch = bch, data->d_build = bld;
    data->d_branchname = QString(bnm), data->d_appname = QString(app),
        data->d_orgname = QString(org), data->d_appdesc = QString(desc);
    data->d_linuxVersion = LinuxVersion{maj, min, rls};
    setQt();
    setWindows();
}

void VersionInfo::company(const QString &co)
{
    data->d_company = co;
}

void VersionInfo::copyright(const QString &co)
{
    data->d_copyright = co;
}

void VersionInfo::legal(const QString &leg)
{
    data->d_legal = leg;
}

void VersionInfo::product(const QString &prod)
{
    data->d_product = prod;
}

QString VersionInfo::dottedString() const
{
    return QString("%1.%2.%3.%4")
        .arg(1000 * major() + minor(), 4, 10, QChar('0'))
        .arg(release()).arg(branch()).arg(build());
}

QString VersionInfo::releaseString(const StringOptions opts) const
{
    QString result= QString(".%1").arg(release(), 3, 10, QChar('0'));
    static QString sReleaseChar("@ABCDEFGHJKLMNPRSTUVWXYZ$");
    const unsigned cRelease = release();
    if (0 == cRelease || (cRelease >= 0xF0 && opts.testFlag(WithoutFinal)))  result.clear();
    else if (cRelease >= 1 && cRelease < sReleaseChar.length()) result = sReleaseChar[cRelease];
    else if (cRelease >= 0xA0 && cRelease <= 0xAF) result = namedRelease("Alpha", opts);
    else if (cRelease >= 0xB0 && cRelease <= 0xBF) result = namedRelease("Beta", opts);
    else if (cRelease >= 0xC0 && cRelease <= 0xCF) result = namedRelease("RC", opts);
    else if (cRelease >= 0xF0 && cRelease <= 0xFF) result = namedRelease("Final", opts);
    return result;}

QString VersionInfo::namedRelease(const char *name, const StringOptions opts) const
{
    QString result(name);
    if ( ! opts.testFlag(WithoutReleaseNumber))
        result += QString::number(release() & 0x0F);
    return result;
}

void VersionInfo::setQt()
{
    QList<signed> tIntList;
    tIntList << major() << minor() << release() << branch() << build();
    data->d_qtVersion = QVersionNumber(tIntList);
}

void VersionInfo::setWindows()
{
    data->d_windowsVersion = WindowsVersion{qint16(major() * 1000 + minor()), release(), qint16(branch()), qint16(build())};
}

// builtin
VersionInfo::VersionInfo() : data(new VersionInfoData) {;}
VersionInfo::VersionInfo(const VersionInfo &rhs) : data{rhs.data} {;}
VersionInfo::~VersionInfo() {;}
VersionInfo &VersionInfo::operator=(const VersionInfo &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

