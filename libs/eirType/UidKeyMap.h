#pragma once
#include "eirType.h"

#include <Uid.h>

#include "DualMap.h"
#include "Key.h"


class EIRTYPE_EXPORT UidKeyMap
{
public:
    UidKeyMap();

private:
    DualMap<Uid, Key> mUidKeyDMap;
};
