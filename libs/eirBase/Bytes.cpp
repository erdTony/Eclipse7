#include "Bytes.h"

Bytes::Bytes() { clear(); }
Bytes::Bytes(const char *pch) { set(pch); }
Bytes::Bytes(const QString &s) { set(s); }
Bytes::Bytes(const AText &other) { set(other); }

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
