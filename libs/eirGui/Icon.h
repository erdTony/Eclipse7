#pragma once
#include "eirGui.h"

#include <QIcon>

class EIRGUI_EXPORT Icon : public QIcon
{
public:
    Icon();
    bool isValid() const { return false; }
};
