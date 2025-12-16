#pragma once
#include "eirCore.h"

#include <QMap>
#include "Key.h"
#include "Value.h"



class EIRCORE_EXPORT KeyValueMap : public QMap<Key, Value>
{
public:
    KeyValueMap();
};
