#pragma once
#include "eirType.h"

#include <QMap>
#include "Key.h"
#include "Value.h"



class EIRTYPE_EXPORT KeyValueMap : public QMap<Key, Value>
{
public:
    KeyValueMap();
};
