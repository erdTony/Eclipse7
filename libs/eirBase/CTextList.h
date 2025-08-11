#pragma once
#include "eirBase.h"

#include "CText.h"

#include <QList>

class EIRBASE_EXPORT CTextList : public CText::List
{
public:
    CTextList();
    CTextList(const QList<CText> other);

public: // const
    CText join(char ch=0) const;
    QStringList toStringList() const;


public: // non-const

public: // pointers
    CTextList it() const;
    CTextList & it();

};


inline CTextList CTextList::it() const { return *this; }
inline CTextList &CTextList::it() { return *this; }
