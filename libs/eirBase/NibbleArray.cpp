#include "NibbleArray.h"

NibbleArray::NibbleArray() : mLength(0) {;}
NibbleArray::NibbleArray(const Count k, const BYTE fill) : mLength(k), mBytes((k + 1) / 2, (fill << 4) | (fill & 0x0F)) {;}
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

BYTE NibbleArray::at(const Index ix) const
{
    const bool cOddIndex = ix & 1;
    const Index cByteIndex = ix >> 1;
    BYTE tByte = mBytes.at(cByteIndex);
    if (cOddIndex)
        tByte >>= 4;
    else
        tByte &= 0x0F;
    return tByte;
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
    return mBytes.toHex();
}

void NibbleArray::set(const Index ix, const BYTE b)
{
    const bool cOddIndex = ix & 1;
    const Index cByteIndex = ix >> 1;
    BYTE tByte = mBytes.at(cByteIndex);
    if (cOddIndex)
        tByte = (tByte & 0xF0) | (b & 0x0F);
    else
        tByte = (tByte & 0x0F) | (b << 4);
    mBytes.assign(cByteIndex, tByte);
}

void NibbleArray::set(const Index ix,
                      const Count k,
                      const BYTE *p)
{
    const NibbleArray cOverlayNibbles(k, p);
    const Index cEnd = ix + Index(k);
    for (Index nix = 0; nix < cEnd; ++nix)
        set(nix, cOverlayNibbles.at(nix - ix));
}


