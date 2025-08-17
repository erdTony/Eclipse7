#pragma once
#include "eirBase.h"

#include "Bytes.h"

#include "Types.h"

class EIRBASE_EXPORT EightCC : public Bytes
{
public: // ctors
    EightCC();
    EightCC(const char * pch);
    EightCC(const AText &atx);
    EightCC(const QString &s);

public: // const
    operator QWORD () const;

public: // non-const

public: // ctors




};

inline EightCC::operator QWORD() const { return Bytes::qword(); }


