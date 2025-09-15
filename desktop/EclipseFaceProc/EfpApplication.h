#pragma once

#include <BaseWidgetApplication.h>

#include <Url.h>

class EfpMainWindow;

#define APP EfpApplication::app()
#define AMW EfpApplication::main()

class EfpApplication : public BaseWidgetApplication
{
    Q_OBJECT
public: // ctors
    EfpApplication(int &argc, char **argv);

public slots:
    void initialize();
    void setup();
    void start();
    void resume();

signals:
    void initialized();
    void setupd();
    void started();
    void resumed();

public: // const
    Url inputUrl() const;

public: // non-const
    void set(const Url &inputUrl);

public: // pointers
    static EfpApplication * app();
    EfpMainWindow * main();


private:
    static EfpApplication * mpInstance;
    EfpMainWindow * mpMainWindow=nullptr;
    ExeSupport mExeSupport;
    Url mInputUrl;
};

inline Url EfpApplication::inputUrl() const { return mInputUrl; }
inline void EfpApplication::set(const Url &inputUrl) { mInputUrl = inputUrl; }
inline EfpApplication *EfpApplication::app() { Q_CHECK_PTR(mpInstance); return mpInstance; }
inline EfpMainWindow *EfpApplication::main() { Q_CHECK_PTR(mpMainWindow); return mpMainWindow; }
