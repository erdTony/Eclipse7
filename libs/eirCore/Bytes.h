#pragma once
#include "eirBase.h"

#include <QByteArray>
#include <QVariant>

#include "AText.h"
#include "Types.h"

class EIRBASE_EXPORT Bytes : public QByteArray
{
public: // ctors
    Bytes();
    Bytes(const char * pch);
    Bytes(const QString &s);
    Bytes(const AText &atx);
    Bytes(const QByteArray &other);
    Bytes(const QVariant &var);
#ifndef Q_CC_MSVC
    Bytes(const OWORD ow);
#endif

public: // const
    BYTE byte() const;
    UINT uint() const;
    Count count() const;
    qsizetype qSizeType() const;
    DWORD dword() const;
    QWORD qword() const;
#ifndef Q_CC_MSVC
    OWORD oword() const;
//    SEWORD seword() const;
#endif
    QByteArray base64() const;
    AText aText() const;

public: // non-const
    void set(const QVariant &var);

public: // pointers
    Bytes it() const;
    Bytes & it();

public:

};

inline Bytes Bytes::it() const { return *this; }
inline Bytes &Bytes::it() { return *this; }

