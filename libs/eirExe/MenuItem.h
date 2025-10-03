#pragma once

#include <QString>
class QAction;
class QShortcut;
class QMenu;

#include <Key.h>
#include <Icon.h>
#include <Types.h>

class MenuItem
{
public: // ctors
    MenuItem();
    MenuItem(const IdNo id, const QString &text, const Key key=Key());

public: // const

public: // non-const

public: // pointers

private:
    IdNo mSortId;
    Key mKey;
    QString mText;
    QString mName;
    Icon mIcon;
    QAction * mpAction=nullptr;
    QShortcut * mpShortcut=nullptr;
    QMenu * mpMenu=nullptr;
};
