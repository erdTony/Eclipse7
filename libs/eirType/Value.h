#pragma once

class Value
{
public:
    Value();
    bool operator == (const Value &rhs) const { (void)rhs; return true; }
};
