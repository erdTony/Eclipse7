#pragma once

#include <QMainWindow>

#include <Types.h>

class BaseMainWindowPage;
class BaseWidgetApplication;
class QStackedWidget;

class MainWindowPageStack : public QMainWindow
{
    Q_OBJECT
public: // ctors
    explicit MainWindowPageStack(BaseWidgetApplication *bwa);

public slots:

signals:

public: // const

public: // non-const
    Index add(BaseMainWindowPage * pBMWP);

public: // pointers
    BaseWidgetApplication* app();
    QStackedWidget* stack();

private:
    BaseWidgetApplication* mpApp=nullptr;
    QStackedWidget* mpStack=nullptr;
};

inline BaseWidgetApplication *MainWindowPageStack::app() { q_check_ptr(mpApp); return mpApp; }
inline QStackedWidget *MainWindowPageStack::stack() { q_check_ptr(mpStack); return mpStack; }


