#pragma once
#include "eirBase.h"

#include <QByteArray>

#include "Types.h"

class EIRBASE_EXPORT NibbleArray : private QByteArray
{
public: // ctors
    NibbleArray();
    NibbleArray(const Count k, const BYTE fill=0);

public: // const
    virtual Count length() const;
    virtual BYTE at(const Index ix) const;
    bool equals(const NibbleArray &other) const;
    virtual bool operator == (const NibbleArray &other) const;

public: // non-const
    void set(const Index ix, const BYTE b);

public: // pointer
    virtual const void * data() const;
    virtual void * data();

public: // static

private:

};

inline bool NibbleArray::operator ==(const NibbleArray &other) const { return equals(other); }
inline const void *NibbleArray::data() const { return QByteArray::data(); }
inline void *NibbleArray::data()  { return QByteArray::data(); }
