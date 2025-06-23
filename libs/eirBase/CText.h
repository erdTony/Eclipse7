#pragma once
#include "eirBase.h"

#include "AText.h"

class EIRBASE_EXPORT CText : public AText
{
public:
    CText();
    CText(const char * pch);
    CText(const QByteArray &ba);
    CText(const QString &s);

public: // pointers
    CText it() const;
    CText & it();

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

inline CText CText::it() const { return *this; }
inline CText & CText::it() { return *this; }
inline char CText::hinge() { return smHingeChar; }
inline void CText::hinge(const char ch) { smHingeChar = ch; }


