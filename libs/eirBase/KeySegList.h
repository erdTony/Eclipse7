#pragma once
#include "eirBase.h"

#include "KeySeg.h"
#include <QList>

#include <QString>
#include <QStringList>


class EIRBASE_EXPORT  KeySegList : public QList<KeySeg>
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
    KeySegList it() const;
    KeySegList & it();

protected: // static
    static char hinge();


};

inline void KeySegList::set() { clear(); }
inline void KeySegList::set(const char *pch) { set(AText(pch)); }
inline void KeySegList::set(const QString &s) { set(AText(s.toLocal8Bit())); }
inline KeySegList KeySegList::it() const { return *this; }
inline KeySegList &KeySegList::it()  { return *this; }
inline char KeySegList::hinge() { return ' '; }
