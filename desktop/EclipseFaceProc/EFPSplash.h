#pragma once

#include <BaseMainWindowPage.h>

class QGridLayout;

class EFPSplash : public BaseMainWindowPage
{
    Q_OBJECT
public: // ctors
    explicit EFPSplash(MainWindowPageStack *pMWPS);

public slots:
    void setup();

signals:

public: // const

public: // non-const

public: // pointers


private:
    QGridLayout * mpLayout=nullptr;
};
