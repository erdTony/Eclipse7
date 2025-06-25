#include "Size.h"

Size::Size(const bool null) : QSize(null ? 0 : -1, null ? 0 : -1) {;}
Size::Size(const QSize other) : QSize(other) {;}
Size::Size(const int w, const int h) : QSize(w, h) {;}
Size::Size(const int dim) : QSize(dim, dim) {;}
Size::Size(const int dim, const Rational aspect) { set(dim, aspect); }
Size::Size(const Size other, const Rational aspect) { set(other, aspect); }

unsigned int Size::area() const
{
    return isValid() ? (width() * height()) : 0;
}

qreal Size::scaleF(const Size &rhs) const
{
    return qMin(qreal(width()) / qreal(rhs.width()),
                qreal(height()) / qreal(rhs.height()));
}

Size Size::set(const Size other, const Rational aspect)
{
    if (other.aspect() == aspect)
    {
        return other;
    }
    else if (other.aspect() < aspect)
    {
        const int w = other.width();
        const int h = w * aspect;
        return Size(w, h);
    }
    else
    {
        const int h = other.width();
        const int w = h * aspect;
        return Size(w, h);
    }
}

