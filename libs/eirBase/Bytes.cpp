#include "Bytes.h"

#include <QBuffer>
#include <QDataStream>

Bytes::Bytes() { clear(); }
Bytes::Bytes(const char *pch) { set(pch); }
Bytes::Bytes(const QString &s) : QByteArray(s.toLocal8Bit()) {;}
Bytes::Bytes(const AText &atx) : QByteArray(atx) {;}
Bytes::Bytes(const QByteArray &other) : QByteArray(other) {;}
Bytes::Bytes(const QVariant &var) { set(var); }

Bytes::Bytes(const OWORD ow)
{
    fill(0, sizeof(ow) + 1);
    std::memcpy(data(), &ow, sizeof(ow));
}

BYTE Bytes::byte() const
{
    BYTE result=0;
    std::memcpy(&result, data(), qMin(qsizetype(sizeof(result)), length()));
    return result;
}

UINT Bytes::uint() const
{
    UINT result=0;
    std::memcpy(&result, data(), qMin(qsizetype(sizeof(result)), length()));
    return result;
}

Count Bytes::count() const
{
    Count result=0;
    std::memcpy(&result, data(), qMin(qsizetype(sizeof(result)), length()));
    return result;
}

qsizetype Bytes::qSizeType() const
{
    qsizetype result=0;
    std::memcpy(&result, data(), qMin(qsizetype(sizeof(result)), length()));
    return result;
}

DWORD Bytes::dword() const
{
    DWORD result=0;
    std::memcpy(&result, data(), qMin(qsizetype(sizeof(result)), length()));
    return result;
}

QWORD Bytes::qword() const
{
    QWORD result=0;
    std::memcpy(&result, data(), qMin(qsizetype(sizeof(result)), length()));
    return result;
}

OWORD Bytes::oword() const
{
    OWORD result=0;
    std::memcpy(&result, data(), qMin(qsizetype(sizeof(result)), length()));
    return result;
}
/*
SEWORD Bytes::seword() const
{
    SEWORD result=0;
    std::memcpy(&result, data(), qMin(qsizetype(sizeof(result)), length()));
    return result;
}
*/
QByteArray Bytes::base64() const
{
    return toBase64();
}

AText Bytes::aText() const
{
    return *this;
}

void Bytes::set(const QVariant &var)
{
    QByteArray tVarBytes;
    QBuffer tBuffer(&tVarBytes);
    QDataStream tStream(&tBuffer);
    tBuffer.open(QIODevice::WriteOnly);
    tStream << var;
    tBuffer.close();
    it() = tVarBytes;
}
