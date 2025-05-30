#pragma once

#include <QList>
#include <QPoint>
#include <QRect>
#include <QSize>
#include <QSizeF>

class SCRect
{
public: // types
    typedef QList<SCRect> List;

public: // ctors
    SCRect();
    SCRect(const QSize sz, const QPoint cpt);
    SCRect(const QRect qrc);

public: // const
    QSize size() const;
    QSizeF sizeF() const;
    QPoint center() const;
    int x() const;
    int y() const;
    int top() const;
    int bottom() const;
    int left() const;
    int right() const;
    int height() const;
    int width() const;
    QPoint topLeft() const;
    bool isEmpty() const;
    bool isNull() const;
    bool contains(const QPoint pt) const;
    QRect toQRect() const;
    SCRect scaled(const unsigned u) const;
    SCRect scaled(const qreal f) const;
    SCRect trimmed(const int i) const;
    SCRect intersected(const SCRect other) const;
    SCRect intersected(const QRect qrc) const;
    SCRect operator * (const unsigned u) const;
    SCRect operator * (const qreal f) const;
    SCRect operator &= (const SCRect other) const;
    operator QRect () const;

public: // non-const
    void height(const int h);
    void width(const int w);
    void size(const int w, const int h);
    SCRect trim(const int i);
    SCRect scale(const unsigned u);
    SCRect scale(const qreal f);
    SCRect offset(const QPoint pt);
    SCRect operator *= (const unsigned u);

    friend SCRect operator & (const SCRect scr, const QRect qrc);

public: // debug
    QString toDebugString() const;

private:
    QSize mSize;
    QPoint mCenter;
};

extern QDebug operator<<(QDebug &stream, const SCRect scr);

inline QSize SCRect::size() const { return mSize; }
inline QSizeF SCRect::sizeF() const { return QSizeF(size()); }
inline QPoint SCRect::center() const { return mCenter; }
inline int SCRect::x() const { return center().x(); }
inline int SCRect::y() const { return center().y(); }
inline int SCRect::height() const { return size().height(); }
inline int SCRect::width() const { return size().width(); }
inline QPoint SCRect::topLeft() const { return QPoint(left(), top()); }
inline bool SCRect::isEmpty() const { return size().isEmpty(); }
inline bool SCRect::isNull() const { return size().isNull(); }
inline QRect SCRect::toQRect() const { return QRect(topLeft(), size()); }
inline SCRect SCRect::operator * (const unsigned u) const { return scaled(u); }
inline SCRect SCRect::operator * (const qreal f) const { return scaled(f); }
inline SCRect SCRect::operator &= (const SCRect other) const { return intersected(other); }
inline SCRect::operator QRect() const { return toQRect(); }
inline void SCRect::height(const int h) { mSize.setHeight(h); }
inline void SCRect::width(const int w) { mSize.setWidth(w); }
inline void SCRect::size(const int w, const int h) { width(w), height(h); }
inline SCRect SCRect::operator *= (const unsigned u) { return scale(u); }


