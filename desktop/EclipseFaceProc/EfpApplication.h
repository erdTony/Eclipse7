#pragma once

#include <BaseWidgetApplication.h>

#include <ExeSupport.h>
#include <Url.h>

class EFPMainWindow;

class EFPApplication : public BaseWidgetApplication
{
    Q_OBJECT
public: // ctors
    EFPApplication(int &argc, char **argv);

public slots:
    void setup();
    void start();
    void resume();

signals:

public: // const

public: // non-const
    void set(const Url &inputUrl);

public: // pointers
    EFPMainWindow * mainWindow();
    ExeSupport & exe();


private:
    EFPMainWindow * mpMainWindow=nullptr;
    ExeSupport mExeSupport;
    Url mInputUrl;
};

inline void EFPApplication::set(const Url &inputUrl) { mInputUrl = inputUrl; }
inline EFPMainWindow *EFPApplication::mainWindow() { Q_CHECK_PTR(mpMainWindow); return mpMainWindow; }
inline ExeSupport &EFPApplication::exe() { return mExeSupport; }
