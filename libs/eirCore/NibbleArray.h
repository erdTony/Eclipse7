#pragma once
#include "eirCore.h"

#include <QByteArray>

#include "Types.h"
#include "XText.h"

class EIRCORE_EXPORT NibbleArray
{
public: // ctors
    NibbleArray();
    NibbleArray(const Count k, const BYTE fill=0);
    NibbleArray(const Count k, const BYTE * p);

public: // const
    virtual bool isNull() const;
    virtual Count length() const;
    virtual BYTE at(const Index ix) const;
    bool isZero() const;
    bool equals(const NibbleArray &other) const;
    XText toHex() const;
    virtual bool operator == (const NibbleArray &other) const;

public: // non-const
    void clear();
    void set(const Index nix, const BYTE b);
    void set(const Index startNix, const Count k, const BYTE *p);
    void fill(const BYTE n, const Count k);

public: // pointer
    virtual const void * data() const;
    virtual void * data(const Index nix);
    virtual void * data();

public: // static

private:
    Count mLength;
    QByteArray mBytes;
};

inline bool NibbleArray::operator ==(const NibbleArray &other) const { return equals(other); }
inline void NibbleArray::clear() { mLength = 0, mBytes.clear(); }
inline const void *NibbleArray::data() const { return mBytes.data(); }
inline void *NibbleArray::data()  { return mBytes.data(); }

