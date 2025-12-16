/*! @file Enumeration.cpp Definitions for Enumeration base class
*/

#include "Enumeration.h"

#include <QStringList>

/*! Enumeration Construct an empty, invalid item */
Enumeration::Enumeration(void) : mValue(0), mName("[null]"), mNameMap(0) {;}

/*! Construct an item from a valid integer

    @arg    const int value a valid integer
    @note   if the specified value is not valid, an invalid item is constructed

*/
Enumeration::Enumeration(Named<int> * p, const int value) : mValue(value), mNameMap(p) {;}

Enumeration::Enumeration(Named<int> * p, const QString & name) : mValue(0), mNameMap(p) { set(name); }

Enumeration::Enumeration(const Enumeration & other) : mValue(other.mValue) , mName(other.mName), mNameMap(other.mNameMap) {;}

Enumeration & Enumeration::operator = (const Enumeration & other)
{
    mValue = other.mValue, mName = other.mName, mNameMap = other.mNameMap;
    return *this;
}

bool Enumeration::isEmpty(void) const
{
    return mNameMap ? mNameMap->isEmpty() : true;
}

Enumeration Enumeration::first(void) const
{
    return isEmpty() ? Enumeration() : Enumeration(mNameMap, mNameMap->first(1));
}

Enumeration Enumeration::last(void) const
{
    return isEmpty() ? Enumeration() : Enumeration(mNameMap, mNameMap->last(1));
}

CText Enumeration::nameOf(const int value) const
{
    QString result = mNameMap ? mNameMap->value(value) : QString();
    return result;
}

int Enumeration::valueOf(const CText & name) const
{
    int result = mNameMap ? mNameMap->value(name) : 0;
    return result;
}

Enumeration & Enumeration::operator ++(void) // prefix ++e
{
    if (mNameMap)
        set(mNameMap->next(mValue));
    return *this;
}

Enumeration Enumeration::operator ++(int)  // postfix e++
{
    Enumeration before(*this);
    if (mNameMap)
        set(mNameMap->next(mValue));
    return before;
}

Enumeration & Enumeration::operator --(void) // prefix --e
{
    if (mNameMap)
        set(mNameMap->previous(mValue));
    return *this;
}

Enumeration Enumeration::operator --(int)  // postfix e--
{
    Enumeration before(*this);
    if (mNameMap)
        set(mNameMap->previous(mValue));
    return before;
}

void Enumeration::set(const int value)
{
    if (mNameMap && mNameMap->contains(value))
    {
        mValue = value;
        mName = mNameMap->value(mValue);
    }
    else
        mNameMap = 0;

    if ( ! mNameMap)
    {
        mValue = 0;
        mName.clear();
    }
}

void Enumeration::set(const CText &name)
{
    if (mNameMap && mNameMap->contains(name))
    {
        mValue = mNameMap->value(name);
        mName = mNameMap->value(mValue);
    }
    else
        mNameMap = 0;

    if ( ! mNameMap)
    {
        mValue = 0;
        mName.clear();
    }
}

void Enumeration::setInvalid(void)
{
    mValue = 0, mName.clear(), mNameMap = 0;
}

bool Enumeration::isValid(void) const
{
    bool result = mNameMap
            && (mNameMap->contains(mValue)
                || 0 == mValue);
    return result;
}

bool Enumeration::isNull(void) const
{
    bool result = ! mNameMap;
    return result;
}

bool Enumeration::is(const int value) const
{
    bool result = isValid() && mValue == value;
    return result;
}

bool Enumeration::operator == (const Enumeration & other) const
{
    bool result = isValid()
            && other.isValid()
            && mValue == other.mValue;
    return result;
}

bool Enumeration::operator < (const Enumeration & other) const
{
    bool result = isValid()
            && other.isValid()
            && mValue < other.mValue;
    return result;
}

Enumeration::operator int (void) const
{
    return value();
}

int Enumeration::value(void) const
{
    return mValue;
}

CText Enumeration::name(void) const
{
    return mName;
}

QList<Enumeration> Enumeration::all(void)
{
    QList<Enumeration> result;
    foreach (int i, values())
        result.append(Enumeration(mNameMap, i));
    return result;
}

QList<int> Enumeration::values(void) const
{
    QList<int> result = mNameMap ? mNameMap->keys() : QList<int>();
    return result;
}

CTextList Enumeration::nameFlags(int f)
{
    QStringList nameList;
    if (mNameMap)
    {
        QList<int> intList = mNameMap->keys();
        foreach (int i, intList)
            if (i && i == (i & f))
                nameList << mNameMap->name(i);
    }
    return nameList;
}

bool Enumeration::isValid(const QString & name)
{
    return (mNameMap && mNameMap->contains(name));
}

int Enumeration::value(const QString & name)
{
    int result = -1;
    if (mNameMap)
        if (mNameMap->contains(name))
            result = mNameMap->value(name);
    return result;
}

QList<Enumeration> Enumeration::parse(const QString & string)
{
    QList<Enumeration> result;

    foreach (QString s, string.simplified()
                              .split(' ', Qt::SkipEmptyParts))
    {
        bool negate = false;
        bool toggle = false;
        if (s.startsWith('-'))
        {
            negate = true;
            s = s.mid(1);
        }
        else if (s.startsWith('!'))
        {
            toggle = true;
            s = s.mid(1);
        }

        if ("~" == s)
        {
            if (negate)
                result.clear();
            else
                result = all();
        }
        else if (s.contains('~'))
        {
            Enumeration min_v(first());
            Enumeration max_v(last());
            if (s.startsWith('~'))
                max_v.set(s.mid(1));
            else if (s.endsWith('~'))
                min_v.set(s.left(s.size()-1));
            else
            {
                int x = s.indexOf('~');
                min_v.set(s.left(x));
                max_v.set(s.mid(x+1));
            }
            if (min_v.isValid() && max_v.isValid())
            {
                Enumeration v(min_v);
                do
                {
                    if (negate)
                        result.removeAll(v);
                    else
                        result.append(v);
                    ++v;
                } while (v.isValid() && v <= max_v);
            }
        }
        else
        {
            Enumeration v(first());
            v.set(s);
            if (v.isValid())
            {
                if (negate)
                    result.removeAll(v);
                else if (toggle)
                {
                    if (result.contains(v))
                        result.removeAll(v);
                    else
                        result.append(v);
                }
                else
                    result.append(v);
            }
        }
    }
    return result;
}

int Enumeration::parseFlags(const QString & string)
{
    int result = 0;
    QList<Enumeration> eList = parse(string);
    foreach (Enumeration e, eList)
        result |= e.value();
    return result;
}
