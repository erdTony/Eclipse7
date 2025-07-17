#include "ActionManager.h"

#include <QAction>

ActionManager::ActionManager(QObject *parent) : QObject{parent} {;}

void ActionManager::add(const Key &key, const Action action)
{
    mKeyActionMap.insert(key, action);
    emit added(key, action);
}

void ActionManager::setup()
{

}

void ActionManager::execute()
{

}

ActionManager::Action ActionManager::add(const Key &key, const QString &name)
{
    Action result = new QAction(name.isEmpty() ? key.last().toString() : name);
    mKeyActionMap.insert(key, result);
    emit added(key, result);
    return result;
}

ActionManager::Action ActionManager::action(const Key &key)
{
    return mKeyActionMap.value(key);
}
