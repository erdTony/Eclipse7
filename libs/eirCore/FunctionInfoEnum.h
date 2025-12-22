#pragma once
#include "eirCore.h"

#include "Enumeration.h"

#define FUNCTIONINFOENUM_ENUM(NV) \
    NV($null,               = 0)  \
    NV(VoidReturn,          = 0x80000000)   \
    NV(AnteConst,           = 0x40000000)   \
    NV(ArgConst,            = 0x00400000)   \
    NV(PostConst,           = 0x00004000)   \
    NV(Virtual,             = 0x20000000)   \
    NV(PureVirtual,         = 0x00002000)   \
    NV(ConstExpr,           = 0x00001000)   \

class EIRCORE_EXPORT FunctionInfoEnum : public Enumeration
{
    DECLARE_ENUMERATION(FunctionInfoEnum, FUNCTIONINFOENUM_ENUM)
};
