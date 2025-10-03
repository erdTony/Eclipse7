#include "Null.h"

Null::Null() { invalidate(); }

Null::Null(const bool is) { set(is); }

bool Null::nullify()
{
    TriBool::set();
    return null();
}

bool Null::full()
{
    reset();
    return null();
}


