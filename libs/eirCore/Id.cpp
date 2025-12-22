#include "Id.h"

#include <MillisecondTime.h>


DEFINE_DATAPROPS(Id, IdData);

QWORD Id::smCtorSeq = 0;

Id::Id(const bool nilUid) : data(new IdData) { uid(nilUid); ctor(); }
Id::Id(const Uid &u)  : data(new IdData) { uid(u); ctor(); }
Id::Id(const Uid &u, const IdNo i)  : data(new IdData) { set(u, i); ctor(); }
Id::Id(const Uid &u, const Key &k) : data(new IdData) { set(u, k); ctor(); }
Id::Id(const Uid &u, const AText &n) : data(new IdData) { set(u, n); ctor(); }
Id::Id(const IdNo i) : data(new IdData) { idno(i); ctor(); }
Id::Id(const Key &k) : data(new IdData) { key(k); ctor(); }
Id::Id(const AText &n) : data(new IdData) { name(n); ctor(); }

bool Id::isNull() const
{
    return uid().isNull();
}

QString Id::toString() const
{
    QString result;
    if ( ! key().isNull())
        result = key().toString();
    else if ( ! name().isNull())
        result = name().simplified().replace(' ', '-');
    else if (0 != idno())
        result = QString::number(idno());
    else if ( ! uid().isNull())
        result = uid().tail();
    else
        result = "{null}";
    return result;
}

void Id::uid(const bool nilUid)
{
    uid(Uid(nilUid));
}

void Id::set(const Uid &u, const IdNo i)
{
    uid(u), idno(i);
}

void Id::set(const Uid &u, const Key &k)
{
    uid(u), key(k);
}

void Id::set(const Uid &u, const AText &n)
{
    uid(u), name(n);
}

void Id::set(const Uid &u, const IdNo i, const Key &k, const AText &n)
{
    uid(u), idno(i), key(k), name(n);
}

void Id::ctor(void)
{
    ctorEms(MillisecondTime::current());
    ctorSeq(++smCtorSeq);
}

void Id::dtor(void) {;}

QDebug operator << (QDebug debug, const Id &ident)
{
    debug << "{Ident:" << ident.uid().tail() << ident.idno()
          << ident.key().toString() << ident.name() << "Ident}";
    return debug;
}

