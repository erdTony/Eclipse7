#pragma once

#include <QList>
#include <QMap>
#include <QPair>

#include <Types.h>

template <typename A, typename B> class DualMap
{
public: // types
    typedef QPair<A, B> AB;
    typedef QList<A> AList;
    typedef QList<B> BList;
    typedef QList<AB> ABList;

public: // ctor
    DualMap() {;}
    DualMap(const ABList abs) { set(abs); }
    DualMap(const ABList as, const ABList bs)  { set(as, bs); }

public: // const
    Count count() const { check(); return mABMap.count(); }
    bool isEmpty() const { check(); return mABMap.isEmpty() || mBAMap.isEmpty(); }
    bool contains(const A &a) const { return mABMap.contains(a); }
    bool contains(const B &b) const { return mBAMap.contains(b); }
    A a(const B &b) const { return mBAMap.value(b); }
    B b(const A &a) const { return mABMap.value(a); }
    A firstA() const { return isEmpty() ? A() : mABMap.firstKey(); }
    B firstB() const { return isEmpty() ? B() : mBAMap.firstKey(); }
    A lastA() const { return isEmpty() ? A() : mABMap.lastKey(); }
    B lastB() const { return isEmpty() ? B() : mBAMap.lastKey(); }
    AList aList() const { return mABMap.keys(); }
    BList bList() const { return mBAMap.keys(); }
    ABList abList() const;

public: // non-const
    void clear();
    void insert(const AB &ab) { insert(ab.first, ab.second); }
    void insert(const A &a, const B &b) { mABMap.insert(a, b); mBAMap.insert(b, a); }
    void remove(const A &a);
    void remove(const B &b);
    void set(const ABList abs);
    void set(const ABList as, const ABList bs);

private:
    void check() const { Q_ASSERT(mABMap.count() == mBAMap.count()); }

private:
    QMap<A, B> mABMap;
    QMap<B, A> mBAMap;
};






