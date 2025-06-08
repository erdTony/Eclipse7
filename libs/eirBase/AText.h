#pragma once

#include <QByteArray>
#include <QString>

class AText : public QByteArray
{
public: // typedef
    typedef QList<AText> List;
    enum Clean
    {
        $null = 0, All, TrimL, TrimR, Trim, Simplify
    };

public: // ctors
    AText() { set(); }
    AText(const char * pch) { set(pch); }
    AText(const QByteArray &ba) { set(ba); }
    AText(const QString &s) { set(s); }

public: // const
    List toList() const;
    QString toString() const;
    operator QString() const;

public: // non-const
    void set();
    void set(const char * pch);
    void set(const QByteArray &ba);
    void set(const QString &s);
    void set(const QByteArrayList &ba);
    void set(const QStringList &s);
    void setList(const char * pch);
    void setList(const QByteArray &ba);
    void setList(const QString &s);


public: // pointers

public: // static
    static char hinge();
    static void hinge(const char ch);

protected: // static
    static bool isValidFirst(const char ch);
    static bool isValidChar(const char ch);

private:
    static char smHingeChar;

private:

};

inline QString AText::toString() const { return QString(constData()); }
inline AText::operator QString() const { return toString(); }
inline void AText::set() { clear(); }
inline void AText::set(const QByteArray &ba) { set(ba.constData()); }
inline void AText::set(const QString &s)  { set(s.toLocal8Bit()); }
inline char AText::hinge() { return smHingeChar; }

