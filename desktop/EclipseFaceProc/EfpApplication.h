#pragma once

#include <BaseWidgetApplication.h>

class QAction;

#include <ActionManager.h>
#include <Url.h>
class BlobStore;

class AppHelper;
class EfpImageReader;
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
    void onPauseResume(const bool checked);

signals:
    void initialized();
    void setupd();
    void started();
    void paused();
    void resumed();

public: // const
    Url inputUrl() const;

public: // non-const
    void inputUrl(const Url &url);

public: // pointers
    static EfpApplication * app();
    EfpMainWindow * main();
    AppHelper * wap();


private:
    static EfpApplication * mpInstance;
    EfpMainWindow * mpMainWindow=nullptr;
//    AppHelper * mpAppHelper=nullptr;
    ActionManager * mpActions=nullptr;
    QAction * mpPauseAction=nullptr;
    QAction * mpResumeAction=nullptr;
    Url mInputUrl;
    Url mBlobUrl;
    BlobStore * mpBlobStore=nullptr;
};

inline Url EfpApplication::inputUrl() const { return mInputUrl; }
inline void EfpApplication::inputUrl(const Url &url) { mInputUrl = url; }
inline EfpApplication *EfpApplication::app() { Q_CHECK_PTR(mpInstance); return mpInstance; }
inline EfpMainWindow *EfpApplication::main() { Q_CHECK_PTR(mpMainWindow); return mpMainWindow; }
//inline AppHelper *EfpApplication::wap()  { Q_CHECK_PTR(mpAppHelper); return mpAppHelper; }
