#pragma once
#include "eirExe.h"

#include <QObject>

#include <QMap>
class QAction;
class QMenu;
class QToolBar;

#include <Key.h>
class Icon;

class EIREXE_EXPORT ActionManager : public QObject
{
    Q_OBJECT
public: // types
    typedef QAction * Action;
    typedef QMap<Key, Action> ActionMap;

public: // ctors
    explicit ActionManager(QObject *parent = nullptr);

public slots:
    void add(const Key &key, const Action action);
    void setup();
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
    QMenu *  menu();
    QToolBar *  toolBar();
    void menu(QMenu * pMenu);
    void toolBar(QToolBar * pBar);

private: // non-const
    void addMenu(const QString &menuText, const Icon &icon, Action result);
    void addToolBar(const QString &menuText, const Icon &icon, Action result);

private:
    ActionMap mActionMap;
    QMenu * mpMainMenu=nullptr;
    QToolBar * mpMainToolBar=nullptr;

};


inline bool ActionManager::hasMenu() const { return nullptr != mpMainMenu; }
inline bool ActionManager::hasToolBar() const  { return nullptr != mpMainToolBar; }
inline QMenu *ActionManager::menu() { Q_CHECK_PTR(mpMainMenu); return mpMainMenu; }
inline QToolBar *ActionManager::toolBar() { Q_CHECK_PTR(mpMainToolBar); return mpMainToolBar; }
inline void ActionManager::menu(QMenu *pMenu) { Q_CHECK_PTR(pMenu); mpMainMenu = pMenu; }
inline void ActionManager::toolBar(QToolBar *pBar) { Q_CHECK_PTR(pBar); mpMainToolBar = pBar; }


