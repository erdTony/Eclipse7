#pragma once
#include "eirMatgeo.h"

#include <QList>
#include <QRect>
#include <QRectF>
#include <QSizeF>

#include "Point.h"
#include "Size.h"

class EIRMATGEO_EXPORT SCRect
{
public: // types
    typedef QList<SCRect> List;

public: // ctors
    SCRect();
    SCRect(const Size sz, const bool centered=true);
    SCRect(const Size sz, const Point cpt);
    SCRect(const QRect qrc);

public: // const
    Size size() const;
    Count area() const;
    QSizeF toQSizeF() const;
    Point center() const;
    int x() const;
    int y() const;
    int top() const;
    int bottom() const;
    int left() const;
    int right() const;
    int height() const;
    int width() const;
    Point topLeft() const;
    bool isEmpty() const;
    bool isNull() const;
    bool contains(const Point pt) const;
    QRect toQRect() const;
    SCRect scaled(const unsigned u) const;
    SCRect scaled(const qreal f) const;
    SCRect trimmed(const int i) const;
    SCRect intersected(const SCRect other) const;
    SCRect intersected(const QRect qrc) const;
    SCRect added(const Point pt) const;
    SCRect operator * (const unsigned u) const;
    SCRect operator * (const qreal f) const;
    SCRect operator + (const Point pt) const;
    SCRect operator &= (const SCRect other) const;
    operator QRect () const;
    operator QRectF () const;

public: // non-const
    void height(const int h);
    void width(const int w);
    void size(const int w, const int h);
    SCRect trim(const int i);
    SCRect scale(const unsigned u);
    SCRect scale(const qreal f);
    SCRect offset(const Point pt);
    SCRect operator *= (const unsigned u);

    friend SCRect operator & (const SCRect scr, const QRect qrc);

public: // debug
    QString toDebugString() const;

private:
    Size mSize;
    Point mCenter;
};

extern EIRMATGEO_EXPORT QDebug operator<<(QDebug &stream, const SCRect scr);

inline Size SCRect::size() const { return mSize; }
inline Count SCRect::area() const { return size().area(); }
inline QSizeF SCRect::toQSizeF() const { return QSizeF((qreal)width(), (qreal)height()); }
inline Point SCRect::center() const { return mCenter; }
inline int SCRect::x() const { return center().x(); }
inline int SCRect::y() const { return center().y(); }
inline int SCRect::height() const { return size().height(); }
inline int SCRect::width() const { return size().width(); }
inline Point SCRect::topLeft() const { return QPoint(left(), top()); }
inline bool SCRect::isEmpty() const { return size().isEmpty(); }
inline bool SCRect::isNull() const { return size().isNull(); }
inline QRect SCRect::toQRect() const { return QRect(topLeft(), size()); }
inline SCRect SCRect::operator * (const unsigned u) const { return scaled(u); }
inline SCRect SCRect::operator +(const Point pt) const { return added(pt); }
inline SCRect SCRect::operator * (const qreal f) const { return scaled(f); }
inline SCRect SCRect::operator &= (const SCRect other) const { return intersected(other); }
inline SCRect::operator QRect() const { return toQRect(); }
inline SCRect::operator QRectF() const { return toQRect(); }
inline void SCRect::height(const int h) { mSize.setHeight(h); }
inline void SCRect::width(const int w) { mSize.setWidth(w); }
inline void SCRect::size(const int w, const int h) { width(w), height(h); }
inline SCRect SCRect::operator *= (const unsigned u) { return scale(u); }


