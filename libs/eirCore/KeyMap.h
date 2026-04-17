#pragma once
#include "eirCore.h"


#include <QVariant>

#include "AText.h"
#include "Key.h"

template <typename T>
class KeyMapT : public QMap<Key, T>
{
public:
    KeyMapT() {;}



};

typedef KeyMapT<QVariant> KeyMap;
typedef KeyMapT<IdNo> KeyNoMap;
typedef KeyMapT<AText> KeyTextMap;
