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
    bool isNull() const;
    Count length() const;
    Count byteLength() const;
    BYTE at(const Index nix) const;
    bool isValidNix(const Index nix) const;
    bool notValidNix(const Index nix) const;
    NibbleArray segment(const Index nix, const Count k) const;
    bool isZero() const;
    bool equals(const NibbleArray &other) const;
    virtual bool operator == (const NibbleArray &other) const;
    XText toHex() const;

public: // non-const
    void clear();
    void append(const BYTE b);
    void set(const Index nix, const BYTE b);
    void set(const Index startNix, const Count k, const BYTE *p);
    void fill(const BYTE n, const Count k);

public: // pointer
    virtual const void * data() const;
    virtual void * data(const Index nix);
    virtual void * data();

public: // static
    static Index byteIndex(const Index nix);

private:
    Count mLength;
    QByteArray mBytes;
};

inline bool NibbleArray::notValidNix(const Index nix) const { return ! isValidNix(nix); }
inline bool NibbleArray::operator ==(const NibbleArray &other) const { return equals(other); }
inline void NibbleArray::clear() { mLength = 0, mBytes.clear(); }
inline const void *NibbleArray::data() const { return mBytes.data(); }
inline void *NibbleArray::data()  { return mBytes.data(); }

