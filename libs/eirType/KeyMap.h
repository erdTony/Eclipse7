#pragma once

#include <QVariant>

#include "AText.h"
#include "Key.h"
#include "KeySeg.h"

template <typename KEY, typename T>
class KeyMapT : public QMap<KEY, T>
{
public:
    KeyMapT() {;}



};

typedef KeyMapT<Key, QVariant> KeyMap;
typedef KeyMapT<Key, AText> KeyTextMap;
typedef KeyMapT<KeySeg, QVariant> KeySegMap;
