#pragma once
#include "eirNetwork.h"

#include "Enumeration.h"

#define URLTYPE_ENUM(NV) \
NV(Null, = 0)  \
    NV(Minimum,)   \

class EIRNETWORK_EXPORT UrlType : public Enumeration
{
    DECLARE_ENUMERATION(UrlType, URLTYPE_ENUM)
};

