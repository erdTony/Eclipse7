#pragma once
#include "eirBase.h"

#include "CText.h"

class EIRBASE_EXPORT CTextList : public CText::List
{
public:
    CTextList();

public: // const
    QStringList toStringList() const;


public: // non-const

public: // pointers
    CTextList it() const;
    CTextList & it();

};


inline CTextList CTextList::it() const { return *this; }
inline CTextList &CTextList::it() { return *this; }
