#pragma once
#include "eirExe.h"

#include <QObject>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QMap>

#include <CText.h>
#include <CTextList.h>
#include <VersionInfo.h>
#include <Types.h>

class EIREXE_EXPORT Options : public QObject
{
    Q_OBJECT
public: // typedef
    typedef QList<QCommandLineOption> OptionList;
    typedef QPair<CText, QString> Positional;
    enum ShowOption
    {
        $nullShow = 0,
        ShowMin,
        ShowNorm,
        ShowMax,
        ShowFull,
    };

public: // ctors
    explicit Options(QObject *parent = nullptr);

public slots:
    void add(const QCommandLineOption opt, const bool addParser=true);
    void addPositional(const CText &name, const QString &desc=QString());
    void process();
    void optionsDialog();
//    void setup();
  //  void execute();

signals:
    void added(const QCommandLineOption opt);
    void addedPositional(const CText &name);


public: // const
    bool isValidPositionalIndex(const Index ix);
    Index positionalIndex(const CText &name);
    bool containsPositional(const CText &name);
    QString positional(const Index ix);
    QString positional(const CText &name);
    bool isError() const;
    QString infoText(const Qt::TextFormat fmt=Qt::PlainText);


public: // non-const
    bool isHelp();
    bool isVer();
    void set(const VersionInfo &vi);
    void addPositionals(const CTextList &names, const QString &desc=QString());
    QCommandLineOption addOption(const CText &name, const QString &desc=QString());
    QCommandLineOption addOption(const char ch, const CText &name, const QString &desc=QString());
    QCommandLineOption addOption(const CTextList &names, const QString &desc=QString());
    void addShowOptions(const ShowOption fallback=$nullShow);
    void addOrgAppOptions();
    void addHelpVerOptions();

public: // static
    static QString showOptName(const ShowOption so);
    static QString showOptShortName(const ShowOption so);

public: // pointers
    QCommandLineParser & parser();


private:
    QCommandLineParser mParser;
    bool mParseError=false;
    QString mErrorText;
    VersionInfo mVersionInfo;
    QMap<CText, QCommandLineOption> mNameOptionMap;
    QList<Positional> mPositionalList;
    ShowOption mFallbackShow=$nullShow;
    const static AText csOrgAppPrefixes;
    const static AText csSettingsPrefixes;
};

inline void Options::set(const VersionInfo &vi) { mVersionInfo = vi; }
inline QCommandLineParser &Options::parser() { return mParser; }
