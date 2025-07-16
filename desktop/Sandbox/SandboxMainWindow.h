#pragma once

#include <QMainWindow>

class QLabel;
class QProgressBar;
class QStatusBar;
class QToolBar;
class QToolButton;
class QWidget;

#include <Size.h>
#include <Types.h>
class ActionManager;
class CommandLine;
class Key;
class KeySeg;

class SandboxApplication;

class SandboxMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SandboxMainWindow(SandboxApplication *parent = nullptr);
    ~SandboxMainWindow();

public slots:
    void initialize();
    void configure();
    void setup();
    void start();
    void set(const QImage &qi);
    void showSwapping(const Count swapPass,
                      const Count numSwaps,
                      const QImage &qi);
    void showFlipped(const QImage &qi);

signals:
    void initialized();
    void configured();
    void setuped();
    void started();


public: // const
    const Size baseSize() const;

public: // non-const
    Count & frameCount();

public: // pointers
    SandboxApplication * app();
    ActionManager * actions();
    QAction * action(const Key &key);
    QToolBar * toolBar();

private slots:
    void setupActions();

private:
    QIcon styleIcon(const KeySeg &key) const;

private:
    SandboxApplication * mpApplication=nullptr;
    ActionManager * mpActions=nullptr;
    QToolBar * mpMainToolBar=nullptr;
    QToolButton * mpQuitButton=nullptr;
    QToolButton * mpFlipButton=nullptr;
    QStatusBar * mpStatusBar=nullptr;
    QProgressBar * mpProgressBar=nullptr;
    QLabel * mpImageLabel=nullptr;
    QPixmap mPixmap;
    const Size cmBaseSize;
    Count mFrameCount=0;
    Count mPassCount=0;
};

inline const Size SandboxMainWindow::baseSize() const { return cmBaseSize; }
inline SandboxApplication *SandboxMainWindow::app() { Q_ASSERT(mpApplication); return mpApplication; }
inline ActionManager *SandboxMainWindow::actions() { Q_ASSERT(mpActions); return mpActions; }
inline QToolBar *SandboxMainWindow::toolBar()  {  Q_ASSERT(mpMainToolBar); return mpMainToolBar; }
