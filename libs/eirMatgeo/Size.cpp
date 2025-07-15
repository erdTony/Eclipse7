#include "Size.h"

#include "SCRect.h"

Size::Size(const bool null) : QSize(null ? 0 : -1, null ? 0 : -1) {;}
Size::Size(const QSize other) : QSize(other) {;}
Size::Size(const int w, const int h) : QSize(w, h) {;}
Size::Size(const int dim) : QSize(dim, dim) {;}
Size::Size(const int dim, const Rational aspect) { set(dim, aspect); }
Size::Size(const Size &other) : QSize(other) {;}
Size::Size(const Size other, const Rational aspect) { set(other, aspect); }

unsigned int Size::area() const
{
    return isValid() ? (width() * height()) : 0;
}

Point Size::center() const
{
    return Point(width() / 2, height() / 2);
}

Size Size::expanded(const Size sz) const
{
    return Size(width() + sz.width(), height() + sz.height());
}

Size Size::scaled(const unsigned int u) const
{
    return Size(width() * u, height() * u);
}

qreal Size::scaleToF(const Size &rhs) const
{
    return qMin(qreal(width()) / qreal(rhs.width()),
                qreal(height()) / qreal(rhs.height()));
}

Size Size::unioned(const Size &rhs) const
{
    const SCRect cOurRect(it());
    const SCRect cRhsRect(rhs);
    return cOurRect.toQRect().united(cRhsRect).size();
}

Size Size::intersected(const Size &rhs) const
{
    const SCRect cOurRect(it());
    const SCRect cRhsRect(rhs);
    return cOurRect.toQRect().intersected(cRhsRect).size();
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

Size Size::unionWith(const Size &rhs)
{
    return it() = unioned(rhs);
}

Size Size::intersectedWith(const Size &rhs)
{
    return it() = intersected(rhs);
}

Size Size::operator =(const Size &rhs)
{
    if (rhs.isValid())
        set(rhs.width(), rhs.height());
    return it();
}


Size Size::set(const int w, const int h)
{
    QSize::setWidth(w), QSize::setHeight(h);
    return it();
}
