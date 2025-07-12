#include "Ident.h"

#include <MillisecondTime.h>


DEFINE_DATAPROPS(Ident, IdentData);

QWORD Ident::smCtorSeq = 0;

Ident::Ident(const bool nilUid) : data(new IdentData) { set(nilUid); ctor(); }
Ident::Ident(const Uid &u)  : data(new IdentData) { set(u); ctor(); }
Ident::Ident(const Uid &u, const ID i)  : data(new IdentData) { set(u, i); ctor(); }
Ident::Ident(const Uid &u, const Key &k) : data(new IdentData) { set(u, k); ctor(); }
Ident::Ident(const Uid &u, const AText &n) : data(new IdentData) { set(u, n); ctor(); }
Ident::Ident(const Uid::Type t) : data(new IdentData) { set(t); ctor(); }
Ident::Ident(const Uid::Type t, const ID i) : data(new IdentData) { set(t, i); ctor(); }
Ident::Ident(const Uid::Type t, const AText &n) : data(new IdentData) { set(t, n); ctor(); }
Ident::Ident(const ID i) : data(new IdentData) { set(i); ctor(); }
Ident::Ident(const Key &k) : data(new IdentData) { set(k); ctor(); }
Ident::Ident(const AText &n) : data(new IdentData) { set(n); ctor(); }

void Ident::set(const bool nilUid)
{
    uid(Uid(nilUid));
}

void Ident::set(const Uid &u)
{
    uid(u);
}

void Ident::set(const Uid &u, const ID i)
{
    uid(u), id(i);
}

void Ident::set(const Uid &u, const Key &k)
{
    uid(u), key(k);
}

void Ident::set(const Uid &u, const AText &n)
{
    uid(u), name(n);
}

void Ident::set(const Uid::Type t)
{
    uid(t);
}

void Ident::set(const Uid::Type t, const ID i)
{
    uid(t), id(i);
}

void Ident::set(const Uid::Type t, const Key &k)
{
    uid(t), key(k);
}

void Ident::set(const Uid::Type t, const AText &n)
{
    uid(t), name(n);
}

void Ident::set(const ID i)
{
    id(i);
}

void Ident::set(const Key &k)
{
    key(k);
}

void Ident::set(const AText &n)
{
    name(n);
}

void Ident::set(const Uid &u, const ID i, const Key &k, const AText &n)
{
    uid(u), id(i), key(k), name(n);
}

void Ident::set(const Uid::Type t, const ID i, const Key &k, const AText &n)
{
    uid(t), id(i), key(k), name(n);
}

void Ident::ctor(void)
{
    ctorEms(MillisecondTime::current());
    ctorSeq(++smCtorSeq);
}

void Ident::dtor(void) {;}
