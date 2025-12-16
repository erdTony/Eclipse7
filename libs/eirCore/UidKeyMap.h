#pragma once
#include "eirCore.h"

#include <Uid.h>

#include "DualMap.h"
#include "Key.h"


class EIRCORE_EXPORT UidKeyMap
{
public:
    UidKeyMap();

private:
    DualMap<Uid, Key> mUidKeyDMap;
};
