#include "Bytes.h"

#include <QBuffer>
#include <QDataStream>

Bytes::Bytes() { clear(); }
Bytes::Bytes(const char *pch) { set(pch); }
Bytes::Bytes(const QString &s) : QByteArray(s.toLocal8Bit()) {;}
Bytes::Bytes(const AText &atx) : QByteArray(atx) {;}
Bytes::Bytes(const QByteArray &other) : QByteArray(other) {;}
Bytes::Bytes(const QVariant &var) { set(var); }

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

SEWORD Bytes::seword() const
{
    SEWORD result=0;
    std::memcpy(&result, data(), qMin(qsizetype(sizeof(result)), length()));
    return result;
}

QByteArray Bytes::base64() const
{
    return toBase64();
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
