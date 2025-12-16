#include "ActionManager.h"

#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>

#include <Icon.h>

ActionManager::ActionManager(QMainWindow *parent) : QObject{(QObject*)parent}, mpMainWindow(parent) {;}

void ActionManager::add(const Key &key, const Action action)
{
    mActionMap.insert(key, action);
    emit added(key, action);
}

void ActionManager::setup(const ActionManager::Flags f)
{
    if (f.testFlag(AddMainMenuBar))
        mpMainMenuBar = mpMainWindow->menuBar();
    if (f.testFlag(AddMainToolbar))
        mpMainToolBar = mpMainWindow->addToolBar("Main");
}

void ActionManager::execute()
{

}

bool ActionManager::contains(const Key &key) const
{
    return mActionMap.contains(key);
}

void ActionManager::addMenu(const QString &menuText, const Icon &icon, Action result)
{

}

void ActionManager::addToolBar(const QString &menuText, const Icon &icon, Action result)
{

}

ActionManager::Action ActionManager::addMenuAction(const QString &menuText, const Icon &icon, const Key &key, const bool addBar)
{
    ActionManager::Action result = add(menuText, key);
    if (icon.isValid()) result->setIcon(icon);
    if (hasMenu()) addMenu(menuText, icon, result);
    if (hasToolBar() && addBar) addToolBar(menuText, icon, result);
    return result;
}

ActionManager::Action ActionManager::addMenuAction(const QString &menuText, const bool addBar)
{
    return addMenuAction(menuText, Icon(), Key(menuText), addBar);
}

ActionManager::Action ActionManager::addMenuAction(const QString &menuText, const Icon &icon, const bool addBar)
{
    return addMenuAction(menuText, icon, Key(menuText), addBar);
}

ActionManager::Action ActionManager::add(const QString &name, Key key)
{
    if (key.isEmpty()) key.set(name);
    Action result = new QAction(name);
    mActionMap.insert(key, result);
    if (hasToolBar())
        mpMainToolBar->addAction(result);
    // TODO add main menubar, handle which menu
    emit added(key, result);
    return result;
}

ActionManager::Action ActionManager::action(const Key &key)
{
    return mActionMap.value(key);
}
