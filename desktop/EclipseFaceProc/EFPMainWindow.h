#pragma once

#include <MainWindowPageStack.h>

#include <QEvent>

class EFPFramesPage;
class EFPSplashPage;

class EFPMainWindow : public MainWindowPageStack
{
    Q_OBJECT

public:
    EFPMainWindow(BaseWidgetApplication *bwa);
    ~EFPMainWindow();

public slots:
    void setup();

signals:
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
    EFPSplashPage * mpSplashPage;
    EFPFramesPage * mpFramesPage;
};


