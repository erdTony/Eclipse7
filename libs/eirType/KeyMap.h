#pragma once

#include <QVariant>

#include "AText.h"
#include "KeySeg.h"
#include "KeySegList.h"

template <typename KEY, typename T>
class KeyMapT : QMap<KEY, T>
{
public:
    KeyMapT() {;}



};

typedef KeyMapT<KeySegList, QVariant> KeyMap;
typedef KeyMapT<KeySegList, AText> KeyTextMap;
typedef KeyMapT<KeySeg, QVariant> KeySegMap;
