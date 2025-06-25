#pragma once

#include <QObject>

#include <QCommandLineOption>
#include <QList>

#include <VersionInfo.h>

class CommandLine;
class KeySeg;
class KeySegList;
class Options;
class Settings;

class ExeSupport : public QObject
{
    Q_OBJECT
public: // typedef
    typedef QList<QCommandLineOption> OptionList;

public: // ctors
    explicit ExeSupport(QObject *parent = nullptr);

public slots:
    void add(const QCommandLineOption opt);
    void add(const ExeSupport::OptionList opts);
    void addOption(const KeySeg &name);
    void addOption(const KeySegList &names);
    void addOption(const KeySeg &name, const QString &desc);
    void addOption(const KeySegList &names, const QString &desc);

signals:

public: // const


public: // non-const



public: // pointers
    CommandLine * cli();
    Options *  opts();
    Settings * stgs();

private:
    VersionInfo mVersionInfo;
    CommandLine * mpCommandLine=nullptr;
    Options * mpOptions=nullptr;
    Settings * mpSettings=nullptr;
};

inline CommandLine *ExeSupport::cli() { Q_CHECK_PTR(mpCommandLine); return mpCommandLine; }
inline Options *ExeSupport::opts() { Q_CHECK_PTR(mpOptions); return mpOptions; }
inline Settings *ExeSupport::stgs() { Q_CHECK_PTR(mpSettings); return mpSettings; }
