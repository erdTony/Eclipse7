#pragma once
#include "eirBase.h"


#include <QtLogging>
#include <QByteArray>
#include <QList>
#include <QString>

class EIRBASE_EXPORT AText : public QByteArray
{
public: // types
    typedef QList<AText> List;
    typedef QPair<AText, AText>  Pair;
    enum Clean
    {
        $null = 0, All, TrimL, TrimR, Trim, Simplify
    };

public: // ctors
    AText() { clear(); }
    AText(const char ch) { set(ch); }
    AText(const char * pch) { set(pch); }
    AText(const QByteArray &ba) { set(ba); }
    AText(const QString &s) { set(s); }

public: // const
    bool isEmpty() const;
    List toList(const char ch=0) const;
    Pair pair(const char ch) const;
    QString toString() const;
    operator QString() const;
    QString operator () () const;

public: // non-const
    void set(const char ch);
    void set(const char * pch);
    void set(const QByteArray &ba);
    void set(const QString &s);
    void set(const QByteArrayList &ba);
    void set(const QStringList &s);
    void setList(const char * pch);
    void setList(const QByteArray &ba);
    void setList(const QString &s);
    AText append(const AText &more);
    AText append(const char ch);
    AText operator += (const AText &more);
    AText operator += (const char ch);

public: // pointers
    AText it() const;
    AText & it();

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
inline AText::operator QString () const { return toString(); }
inline QString AText::operator () () const { return toString(); }
inline void AText::set(const QByteArray &ba) { set(ba.constData()); }
inline void AText::set(const QString &s)  { set(s.toLocal8Bit()); }
inline AText AText::operator +=(const AText &more) { return append(more); }
inline AText AText::operator +=(const char ch) { return append(ch); }
inline AText AText::it() const { return *this; }
inline AText &AText::it() { return *this; }
inline char AText::hinge() { return smHingeChar; }

