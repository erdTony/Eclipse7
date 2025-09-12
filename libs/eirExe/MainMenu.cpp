#include "MainMenu.h"

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("MainMenuBar");
}

bool MainMenu::contains(const Key &key) const
{
    return mIdKeyDMap.contains(key);
}
