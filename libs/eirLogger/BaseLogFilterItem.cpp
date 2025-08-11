#include "BaseLogFilterItem.h"

BaseLogFilterItem::BaseLogFilterItem(const CText name) : CText(name) {;}

bool BaseLogFilterItem::evaluate(const LogItem &item)
{
    return true;
}
