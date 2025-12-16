#pragma once
#include "eirExe.h"


#include <QMainWindow>

#include <QList>
#include <QSize>
#include <QString>

#include <Types.h>

class BaseMainWindowPage;
class QGridLayout;
class QStackedLayout;
class QSizePolicy;
class QTabWidget;
class QWidget;

class EIREXE_EXPORT MainWindowPageStack : public QMainWindow
{
    Q_OBJECT
public: // ctors
    explicit MainWindowPageStack();

public slots:
    void setup();
    void select(BaseMainWindowPage * pPage);
    void updateSizes(const QSize minSize, const QSize maxSize);

signals:
    void setupd();
    void added(const QString n, BaseMainWindowPage * pBMWP);
    void selected(const Index ix, const QString name);
    void selectedPage(BaseMainWindowPage * pPage);
    void activated(BaseMainWindowPage * pBMWP);
    void removing(BaseMainWindowPage * pBMWP);
    void removed(const QString n);

public: // const
    Index nameIndex(BaseMainWindowPage * pBMWP) const;
    Index nameIndex(const QString n) const;
    bool isValidIndex(const Index ix);
    QSize minimumSize() const;
    QSize maximumSize() const;
    QSize clientSize() const;

public: // non-const
    Index add(BaseMainWindowPage * pBMWP);
    bool remove(BaseMainWindowPage * pBMWP);
    bool remove(const Index ix);

public: // pointers
    QTabWidget * tabs();
    QStackedLayout* stack();
    QGridLayout* mainGrid();
    QWidget* stackWidget();
    QSize & minimumSize();
    QSize & maximumSize();

private slots:

private:
    QStackedLayout* mpStackLayout=nullptr;
    QGridLayout* mpMainGrid=nullptr;
    QTabWidget * mpTabWidget=nullptr;
    QWidget* mpStackWidget=nullptr;
    QList<BaseMainWindowPage *> mPageList;
    QSize mMinimumSize;
    QSize mMaximumSize;
};

inline QSize MainWindowPageStack::minimumSize() const { return mMinimumSize; }
inline QSize MainWindowPageStack::maximumSize() const { return mMaximumSize; }
inline QSize MainWindowPageStack::clientSize() const { return contentsRect().size(); }
inline QTabWidget *MainWindowPageStack::tabs() { q_check_ptr(mpTabWidget); return mpTabWidget; }
inline QStackedLayout *MainWindowPageStack::stack() { q_check_ptr(mpStackLayout); return mpStackLayout; }
inline QGridLayout *MainWindowPageStack::mainGrid(){ q_check_ptr(mpMainGrid); return mpMainGrid; }
inline QWidget *MainWindowPageStack::stackWidget() { q_check_ptr(mpStackWidget); return mpStackWidget; }
inline QSize &MainWindowPageStack::minimumSize() { return mMinimumSize; }
inline QSize &MainWindowPageStack::maximumSize() { return mMaximumSize; }


