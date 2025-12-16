#pragma once
#include "eirCore.h"


#include <DataProperty.h>
#include <QSharedData>

#include <QVariant>

#include <AText.h>
#include <Key.h>
#include <Types.h>
#include <Uid.h>
#include <UidList.h>

#define IDENT_DATAPROPS(TND) \
    TND(Uid, uid, 0) \
    TND(IdNo, idno, 0) \
    TND(Key, key, Key()) \
    TND(AText, name, AText()) \
    TND(QVariant, var, QVariant()) \
    TND(Uid, parentuid, Uid()) \
    TND(UidList, childuids, UidList()) \
    TND(Milliseconds, ctorEms, 0) \
    TND(QWORD, ctorSeq, 0) \

class IdentData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(IDENT_DATAPROPS);
public:
    IdentData(void)
    {
        DEFINE_DATAPROPS_CTORS(IDENT_DATAPROPS);
    }
};

class EIRCORE_EXPORT Id
{
    DECLARE_PARENT_DATAPROPS(IDENT_DATAPROPS);
    DECLARE_DATAPROPS(Id, IdentData);

public: // our ctors
    Id(const bool nilUid); // else maxUid
    Id(const Uid &u);
    Id(const Uid &u, const IdNo i);
    Id(const Uid &u, const Key &k);
    Id(const Uid &u, const AText &n);
    Id(const IdNo i);
    Id(const Key &k);
    Id(const AText &n);
    Id(const Uid &u, const IdNo i, const Key &k, const AText &n);

public: // const
    bool isNull() const;
    QString toString() const;

public: // non-const
    void uid(const bool nilUid=true); // else maxUid
    void set(const Uid &u, const IdNo i);
    void set(const Uid &u, const Key &k);
    void set(const Uid &u, const AText &n);
    void set(const Uid &u, const IdNo i, const Key &k, const AText &n);

private:
    static QWORD smCtorSeq;
};

extern EIRCORE_EXPORT QDebug operator << (QDebug debug, const Id &ident);
