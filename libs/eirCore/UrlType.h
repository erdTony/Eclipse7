#pragma once
#include "eirCore.h"

#include "Enumeration.h"

#define URLTYPE_ENUM(NV) \
    NV($null, = 0)  \
    NV(Files,)  \
    NV(SQLite,)  \
    NV(PgSQL,)  \
    NV($other,)   \

class EIRCORE_EXPORT UrlType : public Enumeration
{
    DECLARE_ENUMERATION(UrlType, URLTYPE_ENUM)
};

