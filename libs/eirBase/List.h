#pragma once

#include <QList>

template <class T> class List : public QList<T>
{
public: // ctors
    List() {;}
    List(const QList<T> other) : QList<T>(other) {;}

public: // const

public: // non-const
    List<T> takeFirstList(const qsizetype k);
    void set(const qsizetype ix, const T &t);
};

template<class T> inline List<T> List<T>::takeFirstList(const qsizetype k)
{
    QList<T> result = QList<T>::first(k);
    QList<T>::remove(0, k);
    return result;
}

template<class T>
inline void List<T>::set(const qsizetype ix, const T &t)
{
    while (QList<T>::count() < ix) QList<T>::append(T());
    QList<T>::set(ix, t);
}
