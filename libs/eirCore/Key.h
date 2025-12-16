#pragma once
#include "eirCore.h"


#include "KeySegList.h"

#include <Types.h>

class EIRCORE_EXPORT Key : public KeySegList
{
public: // ctors
    Key() {;}
    Key(const char * pch) : KeySegList(pch) {;}
    Key(const AText &at) : KeySegList(at) {;}
    Key(const KeySegList &other) : KeySegList(other) {;}
    Key(const QString &s) : KeySegList(s) {;}

public: // const
    QWORD hash64() const;

protected: // static
    static char hinge();

};

inline char Key::hinge() { return '/'; }


