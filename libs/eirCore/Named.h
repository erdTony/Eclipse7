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
    T first(const T & t1) const { (void)t1; return isEmpty() ? T() : mNameTDMap.constBegin().key(); }
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
