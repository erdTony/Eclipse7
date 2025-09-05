#pragma once
#include "eirBase.h"

#include "Bytes.h"


#include "Types.h"

class EIRBASE_EXPORT FourCC : public Bytes
{
public: // ctors
    FourCC();
    FourCC(const char * pch);
    FourCC(const AText &atx);
    FourCC(const QString &s);

public: // const
    operator AText () const;
    operator DWORD () const;

public: // non-const

public: // ctors




};

inline FourCC::operator AText() const { return Bytes::aText(); }
inline FourCC::operator DWORD() const { return Bytes::dword(); }

