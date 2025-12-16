#pragma once
#include "eirCore.h"


#include "AText.h"

#include <QList>

/*! class CText Code Text
 */
class EIRCORE_EXPORT CText : public AText
{
public: // types
    typedef QList<CText> List;

public: // ctors
    CText();
    CText(const char ch);
    CText(const char * pch);
    CText(const QByteArray &ba);
    CText(const QString &s);

public: // static
    static char hinge();
    static void hinge(const char ch);

protected: // static
    static bool isValidFirst(const char ch);
    static bool isValidChar(const char ch);

private: // pointers
    CText it() const;
    CText & it();

private:
    static char smHingeChar;

private:

};

inline CText CText::it() const { return *this; }
inline CText & CText::it() { return *this; }
inline char CText::hinge() { return smHingeChar; }
inline void CText::hinge(const char ch) { smHingeChar = ch; }


