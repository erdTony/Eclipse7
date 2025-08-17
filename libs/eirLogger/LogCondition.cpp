#include "LogCondition.h"

#include <QVariant>

LogCondition::LogCondition() : mEnum($null) {;}
LogCondition::LogCondition(const Enum e) : mEnum(e) {;}

bool LogCondition::isValid(const int i)
{
    return i > $null && i < $max;
}

AText LogCondition::text() const
{
    AText result("???");
    switch (mEnum)
    {
    case True:          result = "!! ";  break;
    case False:         result = " ! ";  break;
    case Equal:         result = "== ";  break;
    case NotEqual:      result = "!= ";  break;
    case Less:          result = " < ";  break;
    case LessEqual:
    case NotGreater:    result = " <=";  break;
    case Greater:       result = " > ";  break;
    case GreaterEqual:
    case NotLess:       result = " >=";  break;
    case Positive:      result = " >0";  break;
    case Zero:          result = "==0";  break;
    case Negative:      result = " <0";  break;
    case NonPos:        result = "<=0";  break;
    case NonZero:       result = "!=0";  break;
    case NonNeg:        result = ">=0";  break;
    }
}

void LogCondition::set(const int i)
{
    mEnum = isValid(i) ? Enum(i) : $null;
}
