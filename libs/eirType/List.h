#pragma once

#include <QList>

template <class T> class List : public QList<T>
{
public: // ctors
    List() {;}
    List(const QList<T> other) : QList<T>(other) {;}

public: // const

public: // non-const
    List<T> takeFirst(const qsizetype k);
};

template<class T> inline List<T> List<T>::takeFirst(const qsizetype k)
{
    QList<T> result = QList<T>::first(k);
    QList<T>::remove(0, k);
    return result;
}
