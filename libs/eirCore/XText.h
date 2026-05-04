#pragma once
#include "eirCore.h"

#include "AText.h"

class EIRCORE_EXPORT XText : public AText
{
public: // ctors
    XText();
    XText(const char * pch);
    XText(const QByteArray &ba);
    XText(const QString &s);
    XText(const void * p, const Count k);


public: // non-const
    void set(const void * p, const Count k);

public: // pointers
    XText it() const;
    XText & it();

public: // static
    static char hinge();
    static void hinge(const char ch);

protected: // static
    virtual bool isValidFirst(const char ch) const;
    virtual bool isValidChar(const char ch) const;

private:
    static char smHingeChar;

private:

};

inline XText XText::it() const { return *this; }
inline XText & XText::it() { return *this; }
inline char XText::hinge() { return smHingeChar; }
inline void XText::hinge(const char ch) { smHingeChar = ch; }



