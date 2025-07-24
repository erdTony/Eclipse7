#pragma once
#include "eirType.h"


#include "AText.h"

class EIRTYPE_EXPORT KeySeg : public AText
{
public:
    KeySeg();
    KeySeg(const char ca[]);
    KeySeg(const AText &other);
    KeySeg(const QString &s);

public: // const
    bool equals(const KeySeg &other) const;
    bool equals(const char * pch) const;
    bool operator == (const KeySeg &other) const;
    bool operator == (const char * pch) const;

public: // non-const

public: // pointers

protected: // static
    static bool isValidFirst(const char ch);
    static bool isValidChar(const char ch);

private:


};

inline bool KeySeg::equals(const char *pch) const { return equals(KeySeg(pch)); }
inline bool KeySeg::operator ==(const KeySeg &other) const { return equals(other); }
inline bool KeySeg::operator ==(const char *pch) const { return equals(pch); }
