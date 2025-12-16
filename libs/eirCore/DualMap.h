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
    Count count() const;
    bool isEmpty() const;
    bool contains(const A &a) const { return mABMap.contains(a); }
    bool contains(const B &b) const { return mBAMap.contains(b); }
    A a(const B &b) const;
    B b(const A &a) const;
    AList aList() const;
    BList bList() const;
    ABList abList() const;

public: // non-const
    void clear();
    void insert(const AB &ab);
    void insert(const A &a, const B &b);
    void remove(const A &a);
    void remove(const B &b);
    void set(const ABList abs);
    void set(const ABList as, const ABList bs);

private:
    QMap<A, B> mABMap;
    QMap<B, A> mBAMap;
};



template<typename A, typename B>
inline Count DualMap<A, B>::count() const { Q_ASSERT(mABMap.count() == mBAMap().count()); return mABMap.count(); }
