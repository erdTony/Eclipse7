#pragma once
#include "eirCore.h"

#include <QtLogging>
#include <QByteArray>
#include <QList>
#include <QString>

#include <cstdio>

#include "Types.h"

class EIRCORE_EXPORT AText : public QByteArray
{
public: // types
    typedef QList<AText> List;
    typedef QPair<AText, AText>  Pair;
    enum Clean
    {
        $null = 0, All, TrimL, TrimR, Trim, Simplify
    };

public: // ctors
    AText();
    AText(const char ch);
    AText(const char * pch);
    AText(const QByteArray &ba);
    AText(const QString &s);
    AText(const Count k, const char ch=' ');

public: // const
    bool isEmpty() const;
    bool isValid(const Index ix);
    List toList(const char ch=0) const;
    Pair keyValue(const char ch) const;
    AText at(const IndexList ixs);
    QString toString() const;
    operator QString() const;
    QString operator () () const;
    bool equals(const AText &rhs);
    bool operator == (const AText &rhs);

public: // non-const
    void set(const char ch);
    void set(const char * pch);
    void set(const QByteArray &ba);
    void set(const QString &s);
    void set(const QByteArrayList &ba);
    void set(const QStringList &s);
    void set(const Count k, const char ch=' ');
    int vprintf(const char * format, va_list vlist);
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
inline bool AText::operator ==(const AText &rhs) { return equals(rhs); }
inline void AText::set(const QByteArray &ba) { set(ba.constData()); }
inline void AText::set(const QString &s)  { set(s.toLocal8Bit()); }
inline AText AText::operator +=(const AText &more) { return append(more); }
inline AText AText::operator +=(const char ch) { return append(ch); }
inline AText AText::it() const { return *this; }
inline AText &AText::it() { return *this; }
inline char AText::hinge() { return smHingeChar; }

