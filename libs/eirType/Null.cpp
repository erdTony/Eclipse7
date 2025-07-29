#include "Null.h"

Null::Null() { invalidate(); }

Null::Null(const bool is) : TriBool(is) {;}


bool Null::nullify()
{
    set();
    return null();
}

bool Null::notNull()
{
    reset();
    return null();
}


