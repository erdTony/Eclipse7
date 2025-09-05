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
    EightCC(const QWORD qw);

public: // const
    operator AText () const;
    operator OWORD () const;

public: // non-const

public: // ctors




};

inline EightCC::operator AText() const { return Bytes::aText(); }
inline EightCC::operator OWORD() const { return Bytes::oword(); }


