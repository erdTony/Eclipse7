/*! @file Named.h Declarations for Named Type template
  *
  */
#pragma once

#include "CText.h"
#include "CTextList.h"
#include "DualMap.h"

/*! @class  Named
  * @brief  Specializes DualMap for case insensitive strings
  */
template <class T> class Named
{
public:
    Named(void) {;}
    typedef QList<T> TList;
    static T invalid(void) { return T(); }
    void clear(void) { mNameTDMap.clear(); }
    bool isEmpty(void) const { return mNameTDMap.isEmpty(); }
    int size(void) const { return mNameTDMap.size(); }
    bool contains(const T & t) const { return mNameTDMap.contains(t); }
    bool contains(const CText &name) const { return mNameTDMap.contains(name.toLower()); }
    CText name(const T & t) const { return mNameTDMap.a(t); }
    T value(const CText &name) const { return mNameTDMap.b(name); }
    void insert(const T & t, const CText &name) { mNameTDMap.insert(name.toLower(), t); }
    //T first(const T & t1) const { (void)t1; return isEmpty() ? T() : mNameTDMap.constBegin().key(); }
    CTextList names(void) const { return mNameTDMap.aList(); }
    TList values() const { return mNameTDMap.bList(); }
    void remove(const T & t) { mNameTDMap.remove(t); }
    void remove(const QString & name) { mNameTDMap.remove(name); }
    CText firstName() const { return mNameTDMap.firstA(); }
    CText lastName() const { return mNameTDMap.lastA(); }
    T firstValue() const { return mNameTDMap.firstB(); }
    T lastValue() const { return mNameTDMap.lastB(); }

private:
    DualMap<CText,T> mNameTDMap;
};

/*
    T last(const T & t1) const
    {
        T result(invalid());
        (void)t1;
        if ( ! mNameTDMap.isEmpty())
        {
            typename QMap<T,CText>::const_iterator it = mNameTDMap.constEnd();
            --it;
            result = it.key();
        }
        return result;
    }
    T next(const T & t) const
    {
        T result(invalid());
        typename QMap<T,CText>::const_iterator it = mNameTDMap.find(t);
        if (mNameTDMap.end() != it)
            ++it;
        if (mNameTDMap.end() != it)
            result = it.key();
        return result;
    }
    T previous(const T & t) const
    {
        T result(invalid());
        typename QMap<T,CText>::const_iterator it = mNameTDMap.find(t);
        if (mNameTDMap.begin() != it)
            --it;
        if (mNameTDMap.begin() != it)
            result = it.key();
        return result;
    }
*/
