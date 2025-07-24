#pragma once
#include "eirType.h"

#include <QByteArray>

#include "Types.h"
#include "XText.h"

class EIRTYPE_EXPORT NibbleArray
{
public: // ctors
    NibbleArray();
    NibbleArray(const Count k, const BYTE fill=0);
    NibbleArray(const Count k, const BYTE * p);

public: // const
    virtual Count length() const;
    virtual BYTE at(const Index ix) const;
    bool isZero() const;
    bool equals(const NibbleArray &other) const;
    XText toHex() const;
    virtual bool operator == (const NibbleArray &other) const;

public: // non-const
    void set(const Index ix, const BYTE b);
    void set(const Index ix, const Count k, const BYTE *p);

public: // pointer
    virtual const void * data() const;
    virtual void * data();

public: // static

private:
    Count mLength;
    QByteArray mBytes;
};

inline bool NibbleArray::operator ==(const NibbleArray &other) const { return equals(other); }
inline const void *NibbleArray::data() const { return mBytes.data(); }
inline void *NibbleArray::data()  { return mBytes.data(); }

