#pragma once
#include "eirCore.h"

#include "AText.h"

#include <QByteArrayList>
#include <QMap>
#include <QMultiMap>
#include <QPair>
#include <QStringList>

class EIRCORE_EXPORT ATextList : public AText::List
{
public: // types
    typedef QList<AText::Pair>  PairList;
    typedef QMap<AText, AText>  PairMap;
    typedef QMultiMap<AText, AText>  PairMMap;

public: // ctors
    ATextList();
    ATextList(const AText::List &other);
    ATextList(const QByteArrayList &other);
    ATextList(const QStringList &other);
    ATextList & operator = (const AText::List &other);

public: // const
    AText join(const AText atx) const;
    PairList split(const char ch) const;

public: // non-const

public: // pointers
    ATextList it() const;
    ATextList & it();

public: // static
    static ATextList toList(const PairList atxlpr, const char assign=':');
    static ATextList toList(const PairMMap atxlMm, const char assign=':');
};

inline ATextList ATextList::it() const { return *this; }
inline ATextList &ATextList::it() { return *this; }
