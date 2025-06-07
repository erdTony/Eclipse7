#pragma once

#include "KeySeg.h"
#include <QList>

#include <QString>
#include <QStringList>


class KeySegList : QList<KeySeg>
{
public:
    KeySegList() { set(); }
    KeySegList(const char * pch) { set(pch); }
    KeySegList(const AText &at) { set(at); }
    KeySegList(const QString &s) { set(s); }

public: // const
    QString toString() const;
    operator QString() const;
    QStringList toStringList() const;
    operator QStringList() const;

public: // non-const
    void set();
    void set(const char * pch);
    void set(const AText &at);
    void set(const QString &s);


public: // pointers

protected: // static
    static char hinge();


};

inline void KeySegList::set() { clear(); }
inline void KeySegList::set(const char *pch) { set(AText(pch)); }
inline void KeySegList::set(const QString &s) { set(AText(s.toLocal8Bit())); }
inline char KeySegList::hinge() { return ' '; }
