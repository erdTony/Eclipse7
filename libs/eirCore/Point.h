#pragma once
#include "eirCore.h"

#include <QPoint>

#include <Types.h>

class Size;

class EIRCORE_EXPORT Point : public QPoint
{
public: // ctors
    Point(const bool zero=false);
    Point(const QPoint &other);
    Point(const int x, const int y);
    Point(const Size sz, const Index ix);

public: // const
    virtual bool isNull() const;
    bool isZero() const;
    Point up(const int d=1) const;
    Point nw(const int d=1) const;
    Point no(const int d=1) const;
    Point ne(const int d=1) const;
    Point we(const int d=1) const;
    Point ea(const int d=1) const;
    Point sw(const int d=1) const;
    Point so(const int d=1) const;
    Point se(const int d=1) const;
    int row() const;
    int col() const;


public: // non-const
    Point set(const Point pt);
    Point set(const int x, const int y);
    Point set(const Size sz, const Index ix);
    void nullify();

public: // pointers
    Point it() const;
    Point & it();

public: // static
    static Point nullPoint();
};

inline Point Point::up(const int d) const { return Point(x() + 0, y() + d); }
inline Point Point::nw(const int d) const { return Point(x() - d, y() - d); }
inline Point Point::no(const int d) const { return Point(x() + 0, y() - d); }
inline Point Point::ne(const int d) const { return Point(x() + d, y() - d); }
inline Point Point::we(const int d) const { return Point(x() - d, y() + 0); }
inline Point Point::ea(const int d) const { return Point(x() + d, y() + 0); }
inline Point Point::sw(const int d) const { return Point(x() - d, y() + d); }
inline Point Point::so(const int d) const { return Point(x() + 0, y() + d); }
inline Point Point::se(const int d) const { return Point(x() + d, y() + d); }
inline int Point::row() const { return y(); }
inline int Point::col() const { return x(); }
inline Point Point::it() const { return *this; }
inline Point &Point::it() { return *this; }
