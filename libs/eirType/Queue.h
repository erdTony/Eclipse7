#pragma once

#include <Types.h>

#include "List.h"

template <class T> class Queue
{
public: // types
    typedef List<T> ListT;

public: // ctors
    Queue() {;}
    Queue(const ListT lt) { enqueue(lt); }


public: // const
    bool isEmpty() const;
    Count count() const;
    T peek() const;
    ListT peek(const Count k) const;

public: // non-const
    void clear();
    void enqueue(const T &t);
    void enqueue(const ListT &lt);
    void push(const T &t);
    void push(const ListT &lt);
    T dequeue();
    ListT dequeueList(const Count k);
    T pop();
    ListT pop(const Count k);

public: //

private: //
    ListT mQueue;
};

template<class T> inline bool Queue<T>::isEmpty() const { return mQueue.isEmpty(); }
template<class T> inline Count Queue<T>::count() const { return mQueue.count(); }
template<class T> inline T Queue<T>::peek() const { return mQueue.first(); }
template<class T> inline void Queue<T>::clear() { mQueue.clear(); }
template<class T> inline typename Queue<T>::ListT Queue<T>::peek(const Count k) const { return mQueue.sliced(0, qMin(k, count())); }
template<class T> inline void Queue<T>::enqueue(const T &t) { mQueue.append(t); }
template<class T> inline void Queue<T>::enqueue(const ListT &lt) { mQueue.append(lt); }
template<class T> inline void Queue<T>::push(const T &t) { mQueue.prepend(t); }
template<class T> inline void Queue<T>::push(const ListT &lt) { mQueue.prepend(lt); }
template<class T> inline T Queue<T>::dequeue() { return mQueue.takeFirst(); }
template<class T> inline typename Queue<T>::ListT Queue<T>::dequeueList(const Count k) { return mQueue.takeFirstList(k); }
template<class T> inline T Queue<T>::pop() { return mQueue.takeLast(); }
template<class T> inline typename Queue<T>::ListT Queue<T>::pop(const Count k) { return mQueue.takeLast(k); }

