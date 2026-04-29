#pragma once
#include "eirCore.h"


#include <AText.h>
#include <Types.h>

class EIRCORE_EXPORT KeySeg : public AText
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
    WORD hash16() const;

public: // non-const

public: // pointers

protected: // static
    virtual bool isValidFirst(const char ch) const;
    virtual bool isValidChar(const char ch) const;

private:
    static Seed smHashSeed();


};

inline bool KeySeg::equals(const char *pch) const { return equals(KeySeg(pch)); }
inline bool KeySeg::operator ==(const KeySeg &other) const { return equals(other); }
inline bool KeySeg::operator ==(const char *pch) const { return equals(pch); }
