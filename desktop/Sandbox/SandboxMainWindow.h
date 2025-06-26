#pragma once

#include <QMainWindow>

#include <QPixmap>
#include <QSize>
class QToolBar;
class QToolButton;
class QWidget;

#include <Types.h>
class ActionManager;
class CommandLine;
class Key;
class KeySeg;

class SandboxApplication;
class SandboxScene;

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

signals:
    void initialized();
    void configured();
    void setuped();
    void started();


public: // const

public: // non-const
    Count & frameCount();

public: // pointers
    SandboxApplication * app();
    ActionManager * actions();
    QAction * action(const Key &key);
    SandboxScene * scene();
    QToolBar * toolBar();

private slots:
    void setupActions();

private:
    QIcon styleIcon(const KeySeg &key) const;

private:
    SandboxApplication * mpApplication=nullptr;
    ActionManager * mpActions=nullptr;
    SandboxScene * mpScene=nullptr;
    QToolBar * mpMainToolBar=nullptr;
    QToolButton * mpQuitButton=nullptr;
    QToolButton * mpFlipButton=nullptr;
};

inline SandboxApplication *SandboxMainWindow::app() { Q_ASSERT(mpApplication); return mpApplication; }
inline ActionManager *SandboxMainWindow::actions() { Q_ASSERT(mpActions); return mpActions; }
inline SandboxScene *SandboxMainWindow::scene() {  Q_ASSERT(mpScene); return mpScene; }
inline QToolBar *SandboxMainWindow::toolBar()  {  Q_ASSERT(mpMainToolBar); return mpMainToolBar; }
