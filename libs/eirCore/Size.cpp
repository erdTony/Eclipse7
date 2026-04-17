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

bool Size::isValidIndex(const int index) const
{
    return (index >= 0 && index <= int(area()));
}

Point Size::center() const
{
    return Point(width() / 2, height() / 2);
}

int Size::index(const Point pt) const
{
    return isValid() ? ((pt.y() * width()) + pt.x()) : -1;
}

Point Size::position(const int index) const
{
    Point result;
    if (isValid() && isValidIndex(index))
    {
        result.setX(index % width());
        result.setY(index / width());
    }
    return result;
}

bool Size::less(const Size &rhs) const
{
    return area() < rhs.area();
}

bool Size::isEqualAspect(const Size &rhs) const
{
    const Rational cLtAspectR = aspect();
    const Rational cRtAspectR = rhs.aspect();
    const qreal cLtAspectF = cLtAspectR.toReal();
    const qreal cRtAspectF = cRtAspectR.toReal();
    return qFuzzyCompare(cLtAspectF, cRtAspectF);
}

Size Size::expanded(const Size sz) const
{
    return Size(width() + sz.width(), height() + sz.height());
}

Size Size::expanded(const unsigned int u) const
{
    return Size(width() + u, height() + u);
}

Size Size::trimmed(const unsigned int modulo) const
{
    const unsigned cMask = ~ (modulo - 1);
    return Size(width() & cMask, height() & cMask);
}

Size Size::scaled(const unsigned int u) const
{
    return Size(width() * u, height() * u);
}

Size Size::scaled(const qreal f) const
{
    return Size(width() * f, height() * f);
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
    if (isEqualAspect(other))
    {
        return set(other);
    }
    else if (other.aspect() < aspect)
    {
        const int w = other.width();
        const int h = w / aspect;
        return set(w, h);
    }
    else
    {
        const int h = other.height();
        const int w = h * aspect;
        return set(w, h);
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
