#pragma once
#include "eirExe.h"

#include <QObject>

class QCoreApplication;
class QApplication;
class QMainWindow;
class QAction;

#include <Types.h>
#include <VersionInfo.h>
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

class EIREXE_EXPORT AppHelper : public QObject
{
    Q_OBJECT
public: // types

public: // ctors
    AppHelper(QCoreApplication *capp);
    AppHelper(QApplication *wapp);

public slots:
    void initialize();

signals:
    void initialized();


public:


public: // const
    bool isConsoleApp() const;
    bool isWidgetApp() const;


public: // non-const


public: // pointers
    QCoreApplication * core();
    QCoreApplication * capp();
    QApplication * wapp();
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



inline QCoreApplication *AppHelper::capp() { return isConsoleApp() ? mpConsoleApplication : nullptr; }
inline QApplication *AppHelper::wapp() { return isWidgetApp() ? mpWidgetApplication : nullptr; }
inline bool AppHelper::isConsoleApp() const { return mpConsoleApplication != nullptr; }
inline bool AppHelper::isWidgetApp() const { return mpWidgetApplication != nullptr; }
inline ActionManager *AppHelper::act() { Q_CHECK_PTR(mpActionManager); return mpActionManager; }
inline CommandLine *AppHelper::cli() { Q_CHECK_PTR(mpCommandLine); return mpCommandLine; }
inline MainMenu *AppHelper::menu() { Q_CHECK_PTR(mpMenuBar); return mpMenuBar; }
inline Options *AppHelper::opts() { Q_CHECK_PTR(mpOptions); return mpOptions; }
inline Random *AppHelper::rand()  { Q_CHECK_PTR(mpRandom); return mpRandom; }
inline Settings *AppHelper::stgs() { Q_CHECK_PTR(mpSettings); return mpSettings; }
inline QMainWindow *AppHelper::main() { Q_CHECK_PTR(mpMainWindow); return mpMainWindow; }
inline void AppHelper::main(QMainWindow *mwin)  { Q_CHECK_PTR(mwin); mpMainWindow = mwin; }

