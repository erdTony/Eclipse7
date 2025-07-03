#pragma once

#include <BaseMainWindowPage.h>

class QGridLayout;

class Label;

class EFPSplashPage : public BaseMainWindowPage
{
    Q_OBJECT
public: // ctors
    explicit EFPSplashPage(MainWindowPageStack *pMWPS);

public slots:
    void setup();

signals:

public: // const

public: // non-const

public: // pointers


private:
    QGridLayout * mpMainGrid=nullptr;
    Label * mpEircLabel=nullptr;
    Label * mpIndiLabel=nullptr;
    Label * mpEfpLabel=nullptr;
};
