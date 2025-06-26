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
    Size(const Size other, const Rational aspect);

public: // const
    unsigned area() const;
    Rational aspect() const;
    Point center() const;
    qreal scaleF(const Size &rhs) const;

public: // non-const
    Size set(const bool null=true);
    Size set(const int w, const int h);
    Size set(const int dim);
    Size set(const int dim, const Rational aspect);
    Size set(const Size other, const Rational aspect);

private: // pointer
    Size it() const;
    Size & it();
};

inline Rational Size::aspect() const { return Rational(width(), height()); }
inline Size Size::set(const bool null) { it() = Size(null); return it(); }
inline Size Size::set(const int w, const int h) { it() = Size(w, h); return it(); }
inline Size Size::set(const int dim) { it() = Size(dim); return it(); }
inline Size Size::set(const int dim, const Rational aspect) { return Size(Size(dim), aspect); }
inline Size Size::it() const  { return *this; }
inline Size &Size::it() { return *this; }
