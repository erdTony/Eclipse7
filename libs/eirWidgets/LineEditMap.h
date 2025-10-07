#pragma once
#include "eirWidgets.h"

#include <KeyMap.h>

#include <Key.h>
#include "LineEdit.h"

class EIRWIDGETS_EXPORT LineEditMap : public KeyMapT<Key, LineEdit *>
{
public:
    LineEditMap();
};
