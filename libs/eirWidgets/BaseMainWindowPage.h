#pragma once
#include "eirWidgets.h"


#include <QWidget>

class QSizePolicy;

#include <Size.h>

class MainWindowPageStack;

class EIRWIDGETS_EXPORT BaseMainWindowPage : public QWidget
{
    Q_OBJECT
public: // ctors
    BaseMainWindowPage(const QString &n, MainWindowPageStack *pMWPS);

public slots:
    void name(const QString n);

signals:
    void nameChanged(const QString &n);

public: // const
    QString name() const;
    Index pageIndex() const;
    Size minimumSize() const;

public: // non-const
    void pageIndex(const Index ix);
    void setSize(const QSizePolicy::Policy szp,
                 const Size sz1=Size(), const Size sz2=Size());

public: // pointers
    MainWindowPageStack * pageStack();

private: // non-const

private:
    MainWindowPageStack * mpPageStack=nullptr;
    Size mMinimumSize;
    QString mName;
    Index mPageIndex;
};

inline QString BaseMainWindowPage::name() const { return mName; }
inline Index BaseMainWindowPage::pageIndex() const { return mPageIndex; }
inline Size BaseMainWindowPage::minimumSize() const { return mMinimumSize; }
inline MainWindowPageStack *BaseMainWindowPage::pageStack() { Q_CHECK_PTR(mpPageStack); return mpPageStack; }
inline void BaseMainWindowPage::pageIndex(const Index ix) { mPageIndex = ix; }

