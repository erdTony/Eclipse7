#pragma once

#include <List.h>
#include <Types.h>

#include "Point.h"
#include "Size.h"

template <typename T> class MatrixT
{
public: // ctors
    MatrixT() {;}
    MatrixT(const Size sz, const T &fillT=T()) { fill(sz, fillT); }
    MatrixT(const Size sz, const List<T> &fillList) { fill(sz, fillList); }

public: // const
    Size size() { return mSize; }
    T get(const Point pt) const { return mTList.at(pt.x(), pt.y()); }
    T get(const int x, const int y) const
    { const Index cix = index(x, y);
        return isValid(cix) ? mTList.value(cix) : T(); }

public: // non-const
    void set(const Point pt, const T &t)
    { set(pt.x(), pt.y(), t); }
    void set(const int x, const int y, const T &t)
    { const Index cix = index(x, y);
        if (isValid(cix)) mTList[cix] = t; }
    void fill(const Size sz, const T &t)
    { mSize = sz; mTList.fill(t, mSize.area()); }
    void fill(const Size sz, List<T> &fillList);
    T & ref(const Index ix) { return mTList[ix]; }
    T & ref(const Point pt) { return mTList[index(pt)]; }
    T & operator [] (const Index ix) { return ref(ix); }
    T & operator [] (const Point pt) { return ref(pt); }

private:
    Count area() const { return mSize.area(); }
    Index index(const int x, const int y) const
    { return x + size().width() * y; }
    Index index(const Point pt) const
    { return index(pt.x(), pt.y()); }
    bool isValid(const Index ix) const
    { return ix >= 0 && ix < area(); }
    bool isValid(const int x, const int y) const
    { const Index ix = index(x, y); return isValid(ix); }
    bool isValid(const Point pt) const
    { return isValid(pt.x(), pt.y()); }

private:
    Size mSize;
    List<T> mTList;
};

template<typename T>
inline void MatrixT<T>::fill(const Size sz, List<T> &fillList)
{
    for (Index ix = 0; ix < Index(qMin(sz.area(), fillList.count())); ++ix)
    {
        Point pt(sz, ix);
        set(pt, fillList.takeFirst());
    }
}
