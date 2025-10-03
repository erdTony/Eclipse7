#pragma once

#include <QWidget>

#include <QMap>
#include <QMenuBar>
class QAction;
class QMenu;

#include <DualMap.h>
#include <Key.h>

#include "MenuItem.h"

class MainMenu : private QWidget
{
    Q_OBJECT
public: // ctors
    MainMenu(QWidget *parent=nullptr);

public: // const
    bool contains(const Key &key) const;
    QMenu * operator [] (const Key &key) const;

public: // non-const
    QAction * add(const Key &key);
    void addSeparator(const Key &key);
    void add(const Key &key, QAction * act);

public: // pointers

private:
    QMenuBar * mpMenuBar=nullptr;
    DualMap<IdNo, Key> mIdKeyDMap;
    QMap<IdNo, MenuItem> mIdMenuMap;
};
