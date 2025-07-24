#pragma once
#include "eirType.h"


#include "KeySegList.h"

class EIRTYPE_EXPORT Key : public KeySegList
{
public: // ctors
    Key() {;}
    Key(const char * pch) : KeySegList(pch) {;}
    Key(const AText &at) : KeySegList(at) {;}
    Key(const KeySegList &other) : KeySegList(other) {;}
    Key(const QString &s) : KeySegList(s) {;}


protected: // static
    static char hinge();

};

inline char Key::hinge() { return '/'; }


