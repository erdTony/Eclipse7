#pragma once
#include "eirBase.h"

#include "AText.h"

#include <QByteArrayList>
#include <QPair>
#include <QStringList>

class EIRBASE_EXPORT ATextList : public AText::List
{
public: // types
    typedef QPair<ATextList, ATextList>  Pair;

public: // ctors
    ATextList();
    ATextList(const AText::List &other);
    ATextList(const QByteArrayList &other);
    ATextList(const QStringList &other);
    ATextList & operator = (const AText::List &other);

public: // const
    AText join(const char ch) const;
    Pair split(const char ch) const;

public: // non-const

public: // pointers
    ATextList it() const;
    ATextList & it();

public: //
};

inline ATextList ATextList::it() const { return *this; }
inline ATextList &ATextList::it() { return *this; }
