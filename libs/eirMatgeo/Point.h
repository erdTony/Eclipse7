#pragma once
#include "eirMatgeo.h"

#include <QPoint>

#include <Types.h>

#include "Size.h"

class EIRMATGEO_EXPORT Point : public QPoint
{
public: // ctors
    Point();
    Point(const QPoint &other);
    Point(const int x, const int y);
    Point(const Size sz, const Index ix);

public: // const
    Point up(const int dy=1) const;

public: // non-const
    Point set(const Size sz, const Index ix);

};
