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
    void selected(BaseMainWindowPage * pPage);

public: // pointers
    EfpSplashPage * splash();
    EfpFramesPage * frames();


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

inline EfpSplashPage *EfpMainWindow::splash() { Q_CHECK_PTR(mpSplashPage); return mpSplashPage; }
inline EfpFramesPage *EfpMainWindow::frames() { Q_CHECK_PTR(mpFramesPage); return mpFramesPage; }


