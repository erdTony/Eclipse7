#pragma once
#include "eirBase.h"

#include <QCommandLineOption>
#include <QList>
class QCoreApplication;
class QApplication;
class QMainWindow;
class QAction;

#include "Types.h"
#include "VersionInfo.h"
class Key;
class Icon;
class ActionManager;
class CommandLine;
class CText;
class CTextList;
class MainMenu;
class Options;
class Random;
class Settings;

class EIRBASE_EXPORT ExeSupport
{
public: // types

public: // ctors
    ExeSupport(QCoreApplication *capp);
    ExeSupport(QApplication *wapp);

public:


public: // const


public: // non-const
    void initialize(QObject *parent);

    QAction * addMenuAction(const QString &menuText,
                           const Icon &icon,
                           const Key &key,
                           const bool addBar=true);
    QAction * addMenuAction(const QString &menuText,
                             const bool addBar=true);
    QAction * addMenuAction(const QString &menuText,
                           const Icon &icon,
                           const bool addBar=true);

//    void setup();
  //  void execute();
    //void showWidgetApplication();


public: // pointers
    ActionManager * act();
    CommandLine * cli();
    MainMenu *  menu();
    Options *  opts();
    Random * rand();
    Settings * stgs();
    QMainWindow * main();
    void main(QMainWindow *mwin);

private:
    QCoreApplication * mpConsoleApplication=nullptr;
    QApplication * mpWidgetApplication=nullptr;
    QMainWindow * mpMainWindow=nullptr;
    ActionManager * mpActionManager=nullptr;
    CommandLine * mpCommandLine=nullptr;
    MainMenu * mpMenuBar=nullptr;
    Options * mpOptions=nullptr;
    Random * mpRandom=nullptr;
    Settings * mpSettings=nullptr;
    VersionInfo mVersionInfo;
};

inline ActionManager *ExeSupport::act() { Q_CHECK_PTR(mpActionManager); return mpActionManager; }
inline CommandLine *ExeSupport::cli() { Q_CHECK_PTR(mpCommandLine); return mpCommandLine; }
inline MainMenu *ExeSupport::menu() { Q_CHECK_PTR(mpMenuBar); return mpMenuBar; }
inline Options *ExeSupport::opts() { Q_CHECK_PTR(mpOptions); return mpOptions; }
inline Random *ExeSupport::rand()  { Q_CHECK_PTR(mpRandom); return mpRandom; }
inline Settings *ExeSupport::stgs() { Q_CHECK_PTR(mpSettings); return mpSettings; }
inline QMainWindow *ExeSupport::main() { Q_CHECK_PTR(mpMainWindow); return mpMainWindow; }
inline void ExeSupport::main(QMainWindow *mwin)  { Q_CHECK_PTR(mwin); mpMainWindow = mwin; }
