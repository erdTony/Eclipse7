#pragma once

#include <MainWindowPageStack.h>

#include <QEvent>

class EfpFramesPage;
class EfpSplashPage;

class EfpMainWindow : public MainWindowPageStack
{
    Q_OBJECT

public:
    EfpMainWindow();
    ~EfpMainWindow();

public slots:
    void initialize();
    void setup();
    void start();

signals:
    void initialized();
    void setupd();
    void started();
    void keyEsc();
    void keyF1();

protected:
    virtual bool event(QEvent * pEvent) override;

protected:
    void handleEsc();
    void handleF1();

private:
    bool handleKeyEvent(QEvent * pEvent);


private:
    EfpSplashPage * mpSplashPage;
    EfpFramesPage * mpFramesPage;
};


