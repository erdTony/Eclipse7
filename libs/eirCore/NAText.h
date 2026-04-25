#pragma once

#include "AText.h"

#include "XText.h"

class NAText : public AText
{
public: // ctors
    NAText();
    NAText(const char * pch);
    NAText(const QByteArray &ba);
    NAText(const QString &s);

public: // const
    XText toXText() const;

public: // static
    static char hinge();
    static void hinge(const char ch);

protected: // static
    static bool isValidFirst(const char ch);
    static bool isValidChar(const char ch);

private: // pointers
    NAText it() const;
    NAText & it();

private:
    static char smHingeChar;

private:

};

inline NAText NAText::it() const { return *this; }
inline NAText &NAText::it() { return *this; }
