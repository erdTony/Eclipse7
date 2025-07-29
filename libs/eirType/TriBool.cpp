#include "TriBool.h"

TriBool::TriBool() : mValue(false), mValid(false) {;}
TriBool::TriBool(const bool is) : mValue(is), mValid(true) {;}

bool TriBool::isTrue() const
{
    return true == value() && true == valid();
}

bool TriBool::isFalse() const
{
    return false == value() && true == valid();

}

bool TriBool::isNull() const
{
    return false == value() && false == valid();

}

bool TriBool::isInvalid() const
{
    return ! valid();
}

void TriBool::set(const bool is)
{
    mValue = is, mValid = true;
}

void TriBool::reset()
{
    mValue = false, mValid = true;
}

void TriBool::nullify()
{
    mValue = false, mValid = false;
}

void TriBool::invalidate()
{
    mValue = true, mValid = false;
}
