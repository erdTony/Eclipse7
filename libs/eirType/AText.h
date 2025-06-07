#pragma once

#include <QByteArray>
#include <QString>

class AText : public QByteArray
{
public: // typedef

public: // ctors
    AText() { set(); }
    AText(const char * pch) { set(pch); }
    AText(const QByteArray &ba) { set(ba); }
    AText(const QString &s) { set(s); }


public: // const
    QString toString() const;
    operator QString() const;

public: // non-const
    void set();
    void set(const char * pch);
    void set(const QByteArray &ba);
    void set(const QString &s);


public: // pointers

protected: // static
    static bool isValidFirst(const char ch);
    static bool isValidChar(const char ch);

private:


private:

};

inline QString AText::toString() const { return QString(constData()); }
inline AText::operator QString() const { return toString(); }
inline void AText::set() { clear(); }
inline void AText::set(const QByteArray &ba) { set(ba.constData()); }
inline void AText::set(const QString &s)  { set(s.toLocal8Bit()); }

