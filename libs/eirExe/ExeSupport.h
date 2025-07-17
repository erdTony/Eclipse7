#pragma once
#include "eirExe.h"

#include <QCommandLineOption>
#include <QList>
class QCoreApplication;

#include <Types.h>
#include <VersionInfo.h>
class ActionManager;
class CommandLine;
class KeySeg;
class KeySegList;
class Options;
class Random;
class Settings;

class EIREXE_EXPORT ExeSupport
{
public: // types
    typedef QList<QCommandLineOption> OptionList;

public: // ctors
    explicit ExeSupport(QCoreApplication *app);

public:


public: // const
    bool contains(const KeySeg &name);
    QString positional(const KeySeg &name);
    QString positional(const Index ix);


public: // non-const
    void add(const ExeSupport::OptionList opts);
    void add(const QCommandLineOption opt);
    void addOption(const KeySeg &name);
    void addOption(const KeySegList &names);
    void addOption(const KeySeg &name, const QString &desc);
    void addPositional(const KeySeg &name, const QString &desc);
    void addOption(const KeySegList &names, const QString &desc);
    void addShowOptions();
    void addHelpVerOptions();

    void setup();
    void execute();
    void showWidgetApplication();


public: // pointers
    ActionManager * act();
    CommandLine * cli();
    Options *  opts();
    Random * rand();
    Settings * stgs();

private:
    QCoreApplication * mpCoreApplication=nullptr;
    ActionManager * mpActionManager=nullptr;
    CommandLine * mpCommandLine=nullptr;
    Options * mpOptions=nullptr;
    Random * mpRandom=nullptr;
    Settings * mpSettings=nullptr;
    VersionInfo mVersionInfo;
};

inline ActionManager *ExeSupport::act() { Q_CHECK_PTR(mpActionManager); return mpActionManager; }
inline CommandLine *ExeSupport::cli() { Q_CHECK_PTR(mpCommandLine); return mpCommandLine; }
inline Options *ExeSupport::opts() { Q_CHECK_PTR(mpOptions); return mpOptions; }
inline Random *ExeSupport::rand()  { Q_CHECK_PTR(mpRandom); return mpRandom; }
inline Settings *ExeSupport::stgs() { Q_CHECK_PTR(mpSettings); return mpSettings; }
