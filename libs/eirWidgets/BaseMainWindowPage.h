#pragma once
#include "eirWidgets.h"


#include <QWidget>

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
    void minimumSize(const Size sz);
    void pageIndex(const Index ix);

public: // pointers
    MainWindowPageStack * pageStack();

private slots:

private:
    MainWindowPageStack * mpPageStack=nullptr;
    Size mMinimumSize;
    QString mName;
    Index mPageIndex;
};

inline QString BaseMainWindowPage::name() const { return mName; }
inline Index BaseMainWindowPage::pageIndex() const { return mPageIndex; }
inline Size BaseMainWindowPage::minimumSize() const { return mMinimumSize; }
inline void BaseMainWindowPage::minimumSize(const Size sz) { mMinimumSize = sz; }
inline void BaseMainWindowPage::pageIndex(const Index ix) { mPageIndex = ix; }
