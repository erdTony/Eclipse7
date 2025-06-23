#include "NibbleArray.h"

NibbleArray::NibbleArray() {;}
NibbleArray::NibbleArray(const Count k, const BYTE fill) : QByteArray((k + 1) / 2, (fill << 4) | (fill & 0x0F)) {;}

Count NibbleArray::length() const
{
    return QByteArray::length() / 2;
}

BYTE NibbleArray::at(const Index ix) const
{
    const bool cOddIndex = ix & 1;
    const Index cByteIndex = ix >> 1;
    BYTE tByte = QByteArray::at(cByteIndex);
    if (cOddIndex)
        tByte >>= 4;
    else
        tByte &= 0x0F;
    return tByte;
}

bool NibbleArray::equals(const NibbleArray &other) const
{
    return 0 == compare(QByteArray(other));
}

void NibbleArray::set(const Index ix, const BYTE b)
{
    const bool cOddIndex = ix & 1;
    const Index cByteIndex = ix >> 1;
    BYTE tByte = QByteArray::at(cByteIndex);
    if (cOddIndex)
        tByte = (tByte & 0xF0) | (b & 0x0F);
    else
        tByte = (tByte & 0x0F) | (b << 4);
    QByteArray::assign(cByteIndex, tByte);
}
