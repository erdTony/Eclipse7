#pragma once
#include "eirWidgets.h"


#include <QWidget>

class QGridLayout;
class QSizePolicy;

#include <Size.h>

class MainWindowPageStack;

class EIRWIDGETS_EXPORT BaseMainWindowPage : public QWidget
{
    Q_OBJECT
public: // ctors
    BaseMainWindowPage(const QString &n, QWidget *parent=nullptr);

public slots:
    virtual void setup() = 0;
    virtual void activate() = 0;

signals:
    void setupd();
    void nameChanged(const QString &n);

public: // const
    QString name() const;
    Index pageIndex() const;
    Size minimumSize() const;

public: // non-const
    void name(const QString n);
    void pageIndex(const Index ix);
    void setSizes(const QSizePolicy::Policy szp,
                 const QSize sz1=Size(), const QSize sz2=Size());

public: // pointers
    void stack(MainWindowPageStack * pMWPS);
    MainWindowPageStack * stack();
    QGridLayout * pageGrid();

private: // non-const

private:
    MainWindowPageStack * mpPageStack=nullptr;
    QGridLayout * mpPageGrid=nullptr;
    Size mMinimumSize;
    QString mName;
    Index mPageIndex;
};

inline QString BaseMainWindowPage::name() const { return mName; }
inline Index BaseMainWindowPage::pageIndex() const { return mPageIndex; }
inline Size BaseMainWindowPage::minimumSize() const { return mMinimumSize; }
inline void BaseMainWindowPage::pageIndex(const Index ix) { mPageIndex = ix; }
inline MainWindowPageStack *BaseMainWindowPage::stack() { Q_CHECK_PTR(mpPageStack); return mpPageStack; }
inline void BaseMainWindowPage::stack(MainWindowPageStack *pMWPS) { Q_CHECK_PTR(pMWPS); mpPageStack = pMWPS; }
inline QGridLayout *BaseMainWindowPage::pageGrid() { Q_CHECK_PTR(mpPageGrid); return mpPageGrid; }


