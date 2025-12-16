#include "TriBool.h"

TriBool::TriBool() : mValue(true), mValid(false) {;}
TriBool::TriBool(const bool is) : mValue(is), mValid(true) {;}

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
    mValue = true, mValid = false;
}

void TriBool::invalidate()
{
    mValue = false, mValid = false;
}
