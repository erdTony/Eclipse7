#pragma once
#include "eirMatgeo.h"

#include <QSize>

#include "Point.h"
#include "Rational.h"

class EIRMATGEO_EXPORT Size : public QSize
{
public:
    Size(const bool null=true);
    Size(const QSize other);
    Size(const int w, const int h);
    Size(const int dim);
    Size(const int dim, const Rational aspect);
    Size(const Size &other);
    Size(const Size other, const Rational aspect);

public: // const
    unsigned area() const;
    Rational aspect() const;
    Point center() const;
    Size added(const int i) const;
    Size scaled(const unsigned u) const;
    qreal scaleToF(const Size &rhs) const;
    Size unioned(const Size &rhs) const;
    Size operator | (const Size &rhs) const;
    Size operator + (const unsigned u) const;
    Size operator * (const unsigned u) const;
    operator bool () const;

public: // non-const
    Size set(const bool null=true);
    Size set(const int w, const int h);
    Size set(const int dim);
    Size set(const int dim, const Rational aspect);
    Size set(const Size other, const Rational aspect);
    Size unionWith(const Size &rhs);
    Size operator |= (const Size &rhs);
    Size operator = (const Size &rhs);

private: // pointer
    Size it() const;
    Size & it();
};

inline Rational Size::aspect() const { return Rational(width(), height()); }
inline Size Size::operator |(const Size &rhs) const { return unioned(rhs); }
inline Size Size::operator +(const unsigned int u) const { return added(u); }
inline Size Size::operator *(const unsigned int u) const { return scaled(u); }
inline Size::operator bool() const { return isValid(); }
inline Size Size::set(const bool null) { it() = Size(null); return it(); }
inline Size Size::set(const int dim) { it() = Size(dim); return it(); }
inline Size Size::set(const int dim, const Rational aspect) { return Size(Size(dim), aspect); }
inline Size Size::operator |=(const Size &rhs) { return unionWith(rhs); }
inline Size Size::it() const  { return *this; }
inline Size &Size::it() { return *this; }
