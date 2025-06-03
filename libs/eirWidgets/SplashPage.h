#pragma once

#include "BaseMainWindowPage.h"

#include <QLayout>


class MainWindowPageStack;

class SplashPage : public BaseMainWindowPage
{
    Q_OBJECT
public: // ctors
    SplashPage(const QString name, MainWindowPageStack * pMWS=nullptr);

public slots:

signals:

public: // const

public: // non-const

private:
};
