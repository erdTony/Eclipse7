#pragma once
#include "eirBase.h"

#include <QList>
#include "FSText.h"

#include <QByteArrayList>

#include "ATextList.h"

class EIRBASE_EXPORT FSTextList : public FSText::List
{
public:
    FSTextList();
    FSTextList(const QByteArrayList &bal);
    FSTextList(const FSText s, const char hinge=0);
    FSTextList &operator = (const ATextList &atl);

public:

public: // non-const
    void set(const QByteArrayList &bal);
    void split(const FSText s, char hinge=0);

private: // pointers
    FSTextList it() const;
    FSTextList & it();


};

inline FSTextList FSTextList::it() const { return *this; }
inline FSTextList & FSTextList::it() { return *this; }
