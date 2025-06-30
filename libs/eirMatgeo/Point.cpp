#include "Point.h"

#include "Size.h"

Point::Point() {;}
Point::Point(const QPoint &other) : QPoint(other) {;}
Point::Point(const int x, const int y) : QPoint(x, y) {;}
Point::Point(const Size sz, const Index ix) { set(sz, ix); }



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
    return result;
}
