#include "Point.h"

#include "Size.h"

Point::Point(const bool zero) { set(zero ? Point(0,0) : nullPoint()); }
Point::Point(const QPoint &other) : QPoint(other) {;}
Point::Point(const int x, const int y) : QPoint(x, y) {;}
Point::Point(const Size sz, const Index ix) { set(sz, ix); }

bool Point::isNull() const
{
    return nullPoint() == it();
}

bool Point::isZero() const
{
    return QPoint::isNull();
}

Point Point::set(const Point pt)
{
    return set(pt.x(), pt.y());
}

Point Point::set(const int x, const int y)
{
    setX(x), setY(y);
    return it();
}

Point Point::set(const Size sz, const Index ix)
{
    Point result;
    if (sz.isValid() && ! sz.isEmpty())
    {
        const unsigned cWidth = sz.width();
        const unsigned cY = ix / cWidth;
        const unsigned cX = ix % cWidth;
        result = Point(cX, cY);
    }
    return it() = result;
}

void Point::nullify()
{
    set(nullPoint());
}

Point Point::nullPoint()
{
    return Point(INT_MIN, INT_MIN);
}

