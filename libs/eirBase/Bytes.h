#pragma once
#include "eirBase.h"

#include <QByteArray>

#include "AText.h"
#include "Types.h"

class EIRBASE_EXPORT Bytes : public AText
{
public: // ctors
    Bytes();
    Bytes(const char * pch);
    Bytes(const QString &s);
    Bytes(const AText &other);

public: // const
    DWORD dword() const;
    QWORD qword() const;
    OWORD oword() const;
    SEWORD seword() const;

public: // non-const

public: // pointers

public:

};

