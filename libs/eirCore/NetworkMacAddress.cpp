#include "NetworkMacAddress.h"

#include <QtDebug>

#include "../../doctest/doctest/doctest.h"

NetworkMacAddress::NetworkMacAddress() : m48bits(-1) {;} // invalid
NetworkMacAddress::NetworkMacAddress(const bool local) { set(local); } // null or local
NetworkMacAddress::NetworkMacAddress(const QWORD &u48) { set(u48); }
NetworkMacAddress::NetworkMacAddress(const DWORD &org24, const DWORD &oui24) { set(org24, oui24); }
NetworkMacAddress::NetworkMacAddress(const NAText &natx) { set(natx); }
NetworkMacAddress::NetworkMacAddress(const XText &xtx) { set(xtx); }

TEST_CASE("eirCore/NetworkMacAddress ctors")
{
    NetworkMacAddress nmaInvalid;
    NetworkMacAddress nmaLocal(true);
    NetworkMacAddress nmaNull(false);
    NetworkMacAddress nmaOrgOui(0x00123456, 0x00789ABC);
    NetworkMacAddress nmaNAText("12:34:56-78:9A:BC");
    NetworkMacAddress nmaXText("123456789ABC");

    CHECK( ! nmaInvalid.isValid());
    CHECK(nmaNull.isNull());
    CHECK( ! nmaNull.isValid());
    CHECK( ! nmaLocal.isNull());
    CHECK(nmaLocal.isValid());
}


bool NetworkMacAddress::isNull() const
{
    return 0 == m48bits;
}

bool NetworkMacAddress::isValid() const
{
    return isValid(m48bits);
}

bool NetworkMacAddress::isOui48() const
{
    bool result = false;
    if (isValid()) result = m48bits & 0x0000800000000000;
    return result;
}

bool NetworkMacAddress::equals(const NetworkMacAddress &other) const
{
    return m48bits == other.m48bits;
}

BYTE NetworkMacAddress::at(const Index ix)
{
    BYTE result = 0xFF;
    if (ix >= 0 && ix <= 5)
        result = (m48bits >> (ix * 8)) & 0xFF;
    return result;
}

DWORD NetworkMacAddress::org24() const
{
    DWORD result = 0;
    if (isValid()) result = m48bits >> 24;
    return result;
}

DWORD NetworkMacAddress::oui24() const
{
    DWORD result = 0;
    if (isValid()) result = m48bits & 0x0000000000FFFFFF;
    return result;
}

NAText NetworkMacAddress::toText() const
{
    QByteArray tBA((const char *)(&m48bits), sizeof(m48bits));
    NAText result(tBA.toHex(':'));
    result[9] = '-';
    return result;
}



void NetworkMacAddress::set(const bool local)
{
    clear();
    if (local)
    {
        mNetIf = QNetworkInterface::interfaceFromIndex(2);
        set(NAText(mNetIf.hardwareAddress()));
        qDebug() << Q_FUNC_INFO << local << mNetIf
                 << mNetIf.hardwareAddress() << Qt::hex << m48bits;
    }
}

bool NetworkMacAddress::set(const QWORD &u48)
{
    bool result = false;
    if (isValid(u48)) m48bits = u48, result = true;
    return result;
}

bool NetworkMacAddress::set(const DWORD &org24, const DWORD &oui24)
{
    QWORD t48 = (org24 & 0x00FFFFFF) << 24;
          t48 |= oui24 & 0x00FFFFFF;
    m48bits = isValid(t48) ? t48 : 0;
    return isNull();
}

bool NetworkMacAddress::set(const NAText &natx)
{
    return set(XText(natx));
}

bool NetworkMacAddress::set(const XText &xtx)
{
    QWORD t48 = *QByteArray::fromHex(xtx).constData();
    m48bits = isValid(t48) ? t48 : 0;
    qDebug() << Q_FUNC_INFO << xtx << Qt::hex << t48 << m48bits << isNull();
    return isNull();
}


bool NetworkMacAddress::isValid(const QWORD &u48)
{
    return u48 >= 0x00000000001000000 && u48 <= 0x0000FFFFFFFFFFFF;
}

