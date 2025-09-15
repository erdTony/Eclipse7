#pragma once

#include <BaseMainWindowPage.h>


class Label;

class EfpSplashPage : public BaseMainWindowPage
{
    Q_OBJECT
public: // ctors
    explicit EfpSplashPage(QWidget *parent=nullptr);

public slots:
    virtual void setup();
    virtual void activate();

signals:

public: // const

public: // non-const

public: // pointers


private:
    Label * mpEircLabel=nullptr;
    Label * mpIndiLabel=nullptr;
    Label * mpEfpLabel=nullptr;
};
