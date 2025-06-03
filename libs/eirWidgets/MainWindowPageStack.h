#pragma once

#include <QMainWindow>

#include <QList>
#include <QString>

#include <Types.h>

class BaseMainWindowPage;
class BaseWidgetApplication;
class QGridLayout;
class QStackedLayout;
class QTabWidget;
class QWidget;

class MainWindowPageStack : public QMainWindow
{
    Q_OBJECT
public: // ctors
    explicit MainWindowPageStack(BaseWidgetApplication *pBWA);

public slots:
    void setup();

signals:
    void added(const QString n, BaseMainWindowPage * pBMWP);
    void removing(BaseMainWindowPage * pBMWP);
    void removed(const QString n);

public: // const
    Index nameIndex(BaseMainWindowPage * pBMWP) const;
    Index nameIndex(const QString n) const;
    bool isValidIndex(const Index ix);

public: // non-const
    Index add(BaseMainWindowPage * pBMWP);
    bool remove(BaseMainWindowPage * pBMWP);
    bool remove(const Index ix);


public: // pointers
    BaseWidgetApplication* app();
    QTabWidget * tabs();
    QStackedLayout* stackLayout();
    QGridLayout* mainGrid();
    QWidget* stackWidget();

private slots:

private:
    BaseWidgetApplication* mpApp=nullptr;
    QStackedLayout* mpStackLayout=nullptr;
    QGridLayout* mpMainGrid=nullptr;
    QTabWidget * mpTabWidget=nullptr;
    QWidget* mpStackWidget=nullptr;
    QList<BaseMainWindowPage *> mPageList;
};

inline BaseWidgetApplication *MainWindowPageStack::app() { q_check_ptr(mpApp); return mpApp; }
inline QTabWidget *MainWindowPageStack::tabs() { q_check_ptr(mpTabWidget); return mpTabWidget; }
inline QStackedLayout *MainWindowPageStack::stackLayout() { q_check_ptr(mpStackLayout); return mpStackLayout; }
inline QGridLayout *MainWindowPageStack::mainGrid(){ q_check_ptr(mpMainGrid); return mpMainGrid; }
inline QWidget *MainWindowPageStack::stackWidget() { q_check_ptr(mpStackWidget); return mpStackWidget; }


