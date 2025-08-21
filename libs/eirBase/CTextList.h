#pragma once
#include "eirBase.h"

#include "CText.h"
#include <QList>

#include <QByteArrayList>
#include <QStringList>

#include "ATextList.h"


class EIRBASE_EXPORT CTextList : public CText::List
{
public:
    CTextList();
    CTextList(const QByteArrayList &bal);
    CTextList(const QStringList &qsl);
    CTextList(const ATextList &atxl);
    CTextList(const QList<CText> &other);

public: // const
    CText join(char ch=0) const;
    QStringList toStringList() const;


public: // non-const
    void set(const QByteArrayList &bal);
    void set(const QStringList &qsl);
    void set(const ATextList &atxl);

public: // pointers
    CTextList it() const;
    CTextList & it();

};


inline CTextList CTextList::it() const { return *this; }
inline CTextList &CTextList::it() { return *this; }
