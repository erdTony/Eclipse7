#pragma once

#include <QPair>
#include "Error.h"

template <typename T>
class ResultT : QPair<Error, T>
{
public: // ctors
    ResultT();
    ResultT(const T &t);
    ResultT(const Error &e);
    ResultT(const T &t, const Error &e);

public: // const

public: // non-const

private:
    Error mError;
    T mT;
};

template<typename T> inline ResultT<T>::ResultT() {;}
template<typename T> inline ResultT<T>::ResultT(const T &t) : mT(t) {;}
template<typename T> inline ResultT<T>::ResultT(const Error &e) : mError(e) {;}
template<typename T> inline ResultT<T>::ResultT(const T &t, const Error &e) : mT(t), mError(e)  {;}
