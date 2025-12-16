#pragma once
#include "eirExe.h"

#include <QObject>

#include <QMap>
class QAction;
class QMainWindow;
class QMenuBar;
class QToolBar;

#include <Key.h>
class Icon;

class EIREXE_EXPORT ActionManager : public QObject
{
    Q_OBJECT
public: // types
    typedef QAction * Action;
    typedef QMap<Key, Action> ActionMap;
    enum Flag
    {
        $null = 0,
        AddMainMenuBar     = 0x00000001,
        AddMainToolbar  = 0x00000002,
    };
    Q_DECLARE_FLAGS(Flags, Flag);

public: // ctors
    explicit ActionManager(QMainWindow *parent = nullptr);

public slots:
    void add(const Key &key, const Action action);
    void setup(const ActionManager::Flags f);
    void execute();

signals:
    void added(const Key &key, const Action action);

public: // const
    bool contains(const Key &key) const;
    bool hasMenu() const;
    bool hasToolBar() const;

public: // non-const
    Action add(const QString &name, Key key=Key());
    Action addMenuAction(const QString &menuText,
                           const Icon &icon,
                           const Key &key,
                           const bool addBar=true);
    Action addMenuAction(const QString &menuText,
                           const bool addBar=true);
    Action addMenuAction(const QString &menuText,
                           const Icon &icon,
                           const bool addBar=true);

public: // pointers
    Action action(const Key &key);
    QMenuBar *  menuBar();
    QToolBar *  toolBar();
    void menu(QMenuBar * menuBar);
    void toolBar(QToolBar * pBar);

private: // non-const
    void addMenu(const QString &menuText, const Icon &icon, Action result);
    void addToolBar(const QString &menuText, const Icon &icon, Action result);

private:
    QMainWindow * mpMainWindow=nullptr;
    QMenuBar * mpMainMenuBar=nullptr;
    QToolBar * mpMainToolBar=nullptr;
    ActionMap mActionMap;

};


inline bool ActionManager::hasMenu() const { return nullptr != mpMainMenuBar; }
inline bool ActionManager::hasToolBar() const  { return nullptr != mpMainToolBar; }
inline QMenuBar *ActionManager::menuBar() { Q_CHECK_PTR(mpMainMenuBar); return mpMainMenuBar; }
inline QToolBar *ActionManager::toolBar() { Q_CHECK_PTR(mpMainToolBar); return mpMainToolBar; }
inline void ActionManager::menu(QMenuBar *menuBar) { Q_CHECK_PTR(menuBar); mpMainMenuBar = menuBar; }
inline void ActionManager::toolBar(QToolBar *pBar) { Q_CHECK_PTR(pBar); mpMainToolBar = pBar; }


