#pragma once

#include <QWidget>

class MainWindowPageStack;

class BaseMainWindowPage : public QWidget
{
    Q_OBJECT
public: // ctors
    BaseMainWindowPage(const QString &n, MainWindowPageStack *pMWPS);

public slots:
    void name(const QString n);
    void layout(QLayout *pLayout);

signals:
    void layoutSet(const QLayout * pLayout);
    void nameChanged(const QString &n);

public: // const
    QString name() const;

public: // non-const


public: // pointers
    MainWindowPageStack * pageStack();

private slots:

private:
    MainWindowPageStack * mpPageStack=nullptr;
    QLayout * mpLayout=nullptr;
    QString mName;
};

inline QString BaseMainWindowPage::name() const { return mName; }
