#pragma once
#include "eirBase.h"

#include "Uid.h"

class EIRBASE_EXPORT UidList : public Uid::List
{
public:
    UidList();
    UidList &operator = (const UidList &other);
};
