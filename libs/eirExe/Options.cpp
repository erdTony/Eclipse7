#include "Options.h"

#include <QCoreApplication>
#include <QDialog>
#include <QLabel>
#include <QTimer>

const static AText csOrgAppPrefixes = "%_";
const static AText csSettingsPrefixes = "$";

Options::Options(QObject *parent)
    : QObject{parent}
{
    setObjectName("Options:" + QCoreApplication::applicationName());

}

void Options::add(const QCommandLineOption opt, const bool addParser)
{
    foreach (const QString csSeg, opt.names())
        mNameOptionMap.insert(CText(csSeg), opt);
    if (addParser)
    {
        parser().addOption(opt);
        emit added(opt);
    }
}

void Options::addPositional(const CText &name, const QString &desc)
{
    mPositionalList.append(Positional(name, QString()));
    parser().addPositionalArgument(name, desc);
    emit addedPositional(name);
}

void Options::process()
{
    QStringList tAppArguments = QCoreApplication::arguments();
    mParseError = ! parser().parse(tAppArguments);
    if (mParseError)
        mErrorText = parser().errorText();
    if (isError() || isHelp() || isVer())
    {
        optionsDialog();
    }
    QStringList tParsedList = parser().positionalArguments();
    Q_ASSERT(tParsedList.count() <= mPositionalList.count());
    for (Index ix = 0; ix < tParsedList.count(); ++ix)
        mPositionalList[ix].second = tParsedList.at(ix);
}

void Options::optionsDialog()
{
    QDialog tDialog;
    QLabel tLabel(&tDialog);
    tLabel.setWordWrap(true);
    tLabel.setText(infoText(Qt::PlainText));
    tLabel.setMinimumSize(480, 360);
    tDialog.setWindowTitle(mVersionInfo.product()
                           + (isError() ? " Error" : QString()));
    tDialog.exec();
    QTimer::singleShot(100, qApp, &QCoreApplication::quit);
}

bool Options::isValidPositionalIndex(const Index ix)
{
    return ix >= 0 && ix < mPositionalList.count();
}

Index Options::positionalIndex(const CText &name)
{
    Index result = -1;
    for (Index ix = 0;
         ix < mPositionalList.count() && result < 0;
         ++ix)
        if (name == mPositionalList.at(ix).first)
            result = ix;
    return result;
}

bool Options::containsPositional(const CText &name)
{
    return positionalIndex(name) >= 0;
}

bool Options::isPositionalNull(const Index ix)
{
    return positional(ix).isEmpty();
}

bool Options::isPositionalNull(const CText &name)
{
    return positional(name).isEmpty();
}

QString Options::positional(const Index ix)
{
    return isValidPositionalIndex(ix)
               ? mPositionalList.at(ix).second
               : QString();
}

QString Options::positional(const CText &name)
{
    const Index ix = positionalIndex(name);
    return (ix < 0) ? QString() : positional(ix);
}

bool Options::isError() const
{
    return mParseError || ! mErrorText.isEmpty();
}

QString Options::infoText(const Qt::TextFormat fmt)
{
    Q_UNUSED(fmt); // TODO someday Qt::TextFormat
    QString result;
    if (isError()) result.append(mErrorText + "\n");
    result.append(parser().helpText() + "\n");
    result.append("Version: " + mVersionInfo.toString(VersionInfo::WithDotted));
    return result;
}

bool Options::isHelp()
{
    return parser().isSet("help");
}

bool Options::isVer()
{
    return parser().isSet("version");
}

void Options::addPositionals(const CTextList &names, const QString &desc)
{
    foreach (const CText name, names)
        addPositional(name, desc);
}

QCommandLineOption Options::addOption(const CText &name, const QString &desc)
{
    CTextList names;
    names << name;
    return addOption(names, desc);
}

QCommandLineOption Options::addOption(const char ch, const CText &name, const QString &desc)
{
    CTextList names;
    names << CText(ch);
    names << name;
    return addOption(names, desc);
}

QCommandLineOption Options::addOption(const CTextList &names, const QString &desc)
{
    QCommandLineOption tOpt(names, desc);
    add(tOpt);
    return tOpt;
}

/*
void Options::setup()
{

}

void Options::execute()
{

}
*/

void Options::addShowOptions(const ShowOption fallback)
{
    mFallbackShow = fallback;
    addOption('M', "showmin", "Minimize Application");
    addOption('N', "shownorm", "Show Application as Normal Window");
    addOption('X', "showmax", "Show Application Maximized");
    addOption('F', "showfull", "Show Application Full Screen");
    QCommandLineOption tOpt = addOption("show",
            "Set Application Show Option (min, norm, max, full)");
    if ($nullShow != mFallbackShow)
        tOpt.setDefaultValue(showOptShortName(mFallbackShow));
}

void Options::addOrgAppOptions()
{
    QCommandLineOption tOrgOpt = addOption('O', "org", "Set Organization Name");
    QCommandLineOption tAppOpt = addOption('A', "app", "Set Application Name");
    tOrgOpt.setDefaultValue(mVersionInfo.orgname());
    tAppOpt.setDefaultValue(mVersionInfo.appname());
}

void Options::addHelpVerOptions()
{
    const QCommandLineOption cHelpOpt = parser().addHelpOption();
    const QCommandLineOption cVerOpt = parser().addVersionOption();
    add(cHelpOpt, false);
    add(cVerOpt, false);
}

QString Options::showOptName(const ShowOption so)
{
    return "show" + showOptShortName(so);
}

QString Options::showOptShortName(const ShowOption so)
{
    QString result("$null");
    switch (so)
    {
    case ShowMin:       result = "min";     break;
    case ShowNorm:      result = "norm";    break;
    case ShowMax:       result = "min";     break;
    case ShowFull:      result = "full";    break;
    default:                                break;
    }

    return result;
}
