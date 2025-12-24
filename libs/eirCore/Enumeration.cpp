/*! @file Enumeration.cpp Definitions for Enumeration base class
*/

#include "Enumeration.h"

#include <QStringList>

/*! Enumeration Construct an empty, invalid item */
Enumeration::Enumeration(void) : mValue(0), mName("[null]"), mpNamedMap(0) {;}

/*! Construct an item from a valid integer

    @arg    const int value a valid integer
    @note   if the specified value is not valid, an invalid item is constructed

*/
Enumeration::Enumeration(Named<int> * p, const int value) : mValue(value), mpNamedMap(p) {;}

Enumeration::Enumeration(Named<int> * p, const QString & name) : mValue(0), mpNamedMap(p) { set(name); }

Enumeration::Enumeration(const Enumeration & other) : mValue(other.mValue) , mName(other.mName), mpNamedMap(other.mpNamedMap) {;}

Enumeration & Enumeration::operator = (const Enumeration & other)
{
    mValue = other.mValue, mName = other.mName, mpNamedMap = other.mpNamedMap;
    return *this;
}
#if 1
bool Enumeration::isEmpty(void) const
{
    Q_CHECK_PTR(mpNamedMap);
    return mpNamedMap->isEmpty();
}
#endif
Enumeration Enumeration::first(void) const
{
    return isEmpty() ? Enumeration() : Enumeration(mpNamedMap, mpNamedMap->firstValue());
}

Enumeration Enumeration::last(void) const
{
    return isEmpty() ? Enumeration() : Enumeration(mpNamedMap, mpNamedMap->lastValue());
}

CText Enumeration::nameOf(const int value) const
{
    QString result = mpNamedMap ? mpNamedMap->name(value) : CText();
    return result;
}

int Enumeration::valueOf(const CText & name) const
{
    int result = mpNamedMap ? mpNamedMap->value(name) : 0;
    return result;
}
/*
Enumeration & Enumeration::operator ++(void) // prefix ++e
{
    if (mpNamedMap)
        set(mpNamedMap->next(mValue));
    return *this;
}

Enumeration Enumeration::operator ++(int)  // postfix e++
{
    Enumeration before(*this);
    if (mpNamedMap)
        set(mpNamedMap->next(mValue));
    return before;
}

Enumeration & Enumeration::operator --(void) // prefix --e
{
    if (mpNamedMap)
        set(mpNamedMap->previous(mValue));
    return *this;
}

Enumeration Enumeration::operator --(int)  // postfix e--
{
    Enumeration before(*this);
    if (mpNamedMap)
        set(mpNamedMap->previous(mValue));
    return before;
}
*/
void Enumeration::set(const int value)
{
    if (mpNamedMap && mpNamedMap->contains(value))
    {
        mValue = value;
        mName = mpNamedMap->value(mValue);
    }
    else
        mpNamedMap = 0;

    if ( ! mpNamedMap)
    {
        mValue = 0;
        mName.clear();
    }
}

void Enumeration::set(const CText &name)
{
    if (mpNamedMap && mpNamedMap->contains(name))
    {
        mValue = mpNamedMap->value(name);
        mName = mpNamedMap->value(mValue);
    }
    else
        mpNamedMap = 0;

    if ( ! mpNamedMap)
    {
        mValue = 0;
        mName.clear();
    }
}

void Enumeration::setInvalid(void)
{
    mValue = 0, mName.clear(), mpNamedMap = 0;
}

bool Enumeration::isValid(void) const
{
    bool result = mpNamedMap
            && (mpNamedMap->contains(mValue)
                || 0 == mValue);
    return result;
}

bool Enumeration::isNull(void) const
{
    bool result = ! mpNamedMap;
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
        result.append(Enumeration(mpNamedMap, i));
    return result;
}

QList<int> Enumeration::values(void) const
{
    QList<int> result = mpNamedMap ? mpNamedMap->values() : QList<int>();
    return result;
}

CTextList Enumeration::nameFlags(int f)
{
    QStringList nameList;
    if (mpNamedMap)
    {
        QList<int> intList = mpNamedMap->values();
        foreach (int i, intList)
            if (i && i == (i & f))
                nameList << mpNamedMap->name(i);
    }
    return nameList;
}

bool Enumeration::isValid(const QString & name)
{
    return (mpNamedMap && mpNamedMap->contains(name));
}

int Enumeration::value(const QString & name)
{
    int result = -1;
    if (mpNamedMap)
        if (mpNamedMap->contains(name))
            result = mpNamedMap->value(name);
    return result;
}
#if 0
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
*/
#endif
