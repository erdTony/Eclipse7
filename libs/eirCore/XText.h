#pragma once
#include "eirCore.h"

#include "AText.h"

class EIRCORE_EXPORT XText : public AText
{
public:
    XText();
    XText(const char * pch);
    XText(const QByteArray &ba);
    XText(const QString &s);

public: // pointers
    XText it() const;
    XText & it();

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

inline XText XText::it() const { return *this; }
inline XText & XText::it() { return *this; }
inline char XText::hinge() { return smHingeChar; }
inline void XText::hinge(const char ch) { smHingeChar = ch; }
inline bool XText::isValidFirst(const char ch) { return isxdigit(ch); }
inline bool XText::isValidChar(const char ch) { return isxdigit(ch); }

