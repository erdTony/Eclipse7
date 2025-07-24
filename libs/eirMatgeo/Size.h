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
    int min() const;
    int max() const;
    unsigned area() const;
    Rational aspect() const;
    Point center() const;
    bool less(const Size &rhs) const;
    Size expanded(const Size sz) const;
    Size expanded(const unsigned u) const;
    Size scaled(const unsigned u) const;
    qreal scaleToF(const Size &rhs) const;
    Size unioned(const Size &rhs) const;
    Size intersected(const Size &rhs) const;
    bool operator < (const Size &rhs) const;
    Size operator | (const Size &rhs) const;
    Size operator & (const Size &rhs) const;
    Size operator * (const unsigned u) const;
    Size operator + (const unsigned u) const;

public: // non-const
    Size set(const bool null=true);
    Size set(const int w, const int h);
    Size set(const int dim);
    Size set(const int dim, const Rational aspect);
    Size set(const Size other, const Rational aspect);
    Size unionWith(const Size &rhs);
    Size intersectedWith(const Size &rhs);
    Size operator |= (const Size &rhs);
    Size operator &= (const Size &rhs);
    Size operator = (const Size &rhs);

private: // pointer
    Size it() const;
    Size & it();
};

inline int Size::min() const { return qMin(width(), height()); }
inline int Size::max() const { return qMax(width(), height()); }
inline Rational Size::aspect() const { return Rational(width(), height()); }
inline bool Size::operator <(const Size &rhs) const { return less(rhs); }
inline Size Size::operator |(const Size &rhs) const { return unioned(rhs); }
inline Size Size::operator &(const Size &rhs) const { return intersected(rhs); }
inline Size Size::operator *(const unsigned int u) const { return scaled(u); }
inline Size Size::operator +(const unsigned int u) const { return expanded(u); }
inline Size Size::set(const bool null) { it() = Size(null); return it(); }
inline Size Size::set(const int dim) { it() = Size(dim); return it(); }
inline Size Size::set(const int dim, const Rational aspect) { return Size(Size(dim), aspect); }
inline Size Size::operator |=(const Size &rhs) { return unionWith(rhs); }
inline Size Size::operator &=(const Size &rhs) { return intersectedWith(rhs); }
inline Size Size::it() const  { return *this; }
inline Size &Size::it() { return *this; }
