#pragma once

#include <QNetworkInterface>

#include "NAText.h"
#include "Types.h"
#include "XText.h"

class NetworkMacAddress
{
public: // ctors
    NetworkMacAddress(); // invalid
    NetworkMacAddress(const bool local); // null or local
    NetworkMacAddress(const QWORD &u48);
    NetworkMacAddress(const DWORD &org24, const DWORD &oui24);
    NetworkMacAddress(const NAText &natx);
    NetworkMacAddress(const XText &xtx);

public: // const
    bool isNull() const;
    bool isValid() const;
    bool isOui48() const;
    bool equals(const NetworkMacAddress &other) const;
    BYTE at(const Index ix);
    DWORD org24() const;
    DWORD oui24() const;
    QWORD u48() const;
    NAText toText() const;
    bool operator == (const NetworkMacAddress &other);

public: // non-const
    void clear();
    void set(const bool local); // null or local
    bool set(const QWORD &u48);
    bool set(const DWORD &org24, const DWORD &oui24);
    bool set(const NAText &natx);
    bool set(const XText &xtx);

public: // static
    static bool isValid(const QWORD &u48);
    static bool isValid(const NAText &natx);
    static bool isValid(const XText &xtx);

private:
    QWORD m48bits=0;
    QNetworkInterface mNetIf;
};

inline QWORD NetworkMacAddress::u48() const { return m48bits; }
inline bool NetworkMacAddress::operator ==(const NetworkMacAddress &other) { return equals(other); }
inline void NetworkMacAddress::clear() { m48bits = 0; }
