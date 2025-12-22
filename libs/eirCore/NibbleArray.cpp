#include "NibbleArray.h"

NibbleArray::NibbleArray() : mLength(0) {;}
NibbleArray::NibbleArray(const Count k, const BYTE n) { fill(k, n); }
NibbleArray::NibbleArray(const Count k, const BYTE * p) : mLength(k), mBytes(QByteArray::fromRawData((const char *)p, (k + 1) / 2)) {;}

bool NibbleArray::isNull() const
{
    return mBytes.isNull();
}

Count NibbleArray::length() const
{
    Q_ASSERT(Count(mBytes.length()) >= Count(mLength / 2 + mLength % 2));
    return mLength;
}

Count NibbleArray::byteLength() const
{
    return (mLength + 1) >> 1;
}

BYTE NibbleArray::at(const Index nix) const
{
    if (notValidNix(nix)) return 0xFF;
    const bool cOddIndex = nix & 1;
    const Index cByteIndex = byteIndex(nix);
    BYTE tByte = mBytes.at(cByteIndex);
    if (cOddIndex)
        tByte >>= 4;
    else
        tByte &= 0x0F;
    return tByte;
}

bool NibbleArray::isValidNix(const Index nix) const
{
    return nix >= 0 && nix < Index(length());
}

NibbleArray NibbleArray::segment(const Index nix, const Count k) const
{
    NibbleArray result;
    Index tNix = nix;
    Index tEnd = nix + (Index)k;
    while (isValidNix(tNix) && tNix < tEnd)
        result.append(at(tNix++));
    // TODO efficiently
    return result;
}

bool NibbleArray::isZero() const
{
    for (Index nix = 0; nix < Index(length()); ++nix)
        if (at(nix) != 0) return false;
    return true;
}

bool NibbleArray::equals(const NibbleArray &other) const
{
    return (length() == other.length())
           && (0 == mBytes.compare(other.mBytes));
}

XText NibbleArray::toHex() const
{
    return mBytes.toHex().first(length());
}

void NibbleArray::append(const BYTE b)
{
    set(length(), b);
}

void NibbleArray::set(const Index nix, const BYTE b)
{
    const bool cOddIndex = nix & 1;
    const Index cByteIndex = nix >> 1;
    if (cByteIndex < mBytes.length())
    {
        const Count cAppendCount = cByteIndex - mBytes.length();
        mBytes.append(cAppendCount, 0);
    }
    BYTE tByte = mBytes.at(cByteIndex);
    if (cOddIndex)
        tByte = (tByte & 0xF0) | (b & 0x0F);
    else
        tByte = (tByte & 0x0F) | (b << 4);
    mBytes.assign(cByteIndex, tByte);
}

void NibbleArray::set(const Index startNix,
                      const Count k,
                      const BYTE *p)
{
    const NibbleArray cOverlayNibbles(k, p);
    const Index cEndNix = startNix + Index(k);
    for (Index nix = 0; nix < cEndNix; ++nix)
        set(nix, cOverlayNibbles.at(nix));
}

void NibbleArray::fill(const BYTE n, const Count k)
{
    const Count cByteCount = (k + 1) / 2;
    const BYTE cByteValue = (n << 4) | (n & 0x0F);
    mLength = k;
    mBytes = QByteArray(cByteCount, cByteValue);
}

void *NibbleArray::data(const Index nix)
{
    const Index cByteIndex = nix >> 1;
    return mBytes.data() + cByteIndex;
}

Index NibbleArray::byteIndex(const Index nix)
{
    return nix >> 1;
}


