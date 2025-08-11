#pragma once
#include "eirLogger.h"

#include <CText.h>

class LogItem;

class EIRLOGGER_EXPORT BaseLogFilterItem : public CText
{
public:
    BaseLogFilterItem(const CText name=CText());
    virtual bool evaluate(const LogItem &item);
};
