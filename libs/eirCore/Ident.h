#pragma once
#include "eirCore.h"


#include <DataProperty.h>
#include <QSharedData>

#include <QVariant>

#include <AText.h>
#include <Key.h>
#include <Types.h>
#include <Uid.h>

#define IDENT_DATAPROPS(TND) \
    TND(Uid, uid, 0) \
    TND(ID, id, 0) \
    TND(Key, key, Key()) \
    TND(AText, name, AText()) \
    TND(QVariant, description, QVariant()) \
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

class EIRTYPE_EXPORT Ident
{
    DECLARE_PARENT_DATAPROPS(IDENT_DATAPROPS);
    DECLARE_DATAPROPS(Ident, IdentData);

public: // our ctors
    Ident(const bool nilUid); // else maxUid
    Ident(const Uid &u);
    Ident(const Uid &u, const ID i);
    Ident(const Uid &u, const Key &k);
    Ident(const Uid &u, const AText &n);
    Ident(const Uid::Type t);
    Ident(const Uid::Type t, const ID i);
    Ident(const Uid::Type t, const Key &k);
    Ident(const Uid::Type t, const AText &n);
    Ident(const ID i);
    Ident(const Key &k);
    Ident(const AText &n);
    Ident(const Uid &u, const ID i, const Key &k, const AText &n);
    Ident(const Uid::Type t, const ID i, const Key &k, const AText &n);

public: // const
    bool isNull() const;
    QString toString() const;

public: // non-const
    void set(const bool nilUid=true); // else maxUid
    void set(const Uid &u);
    void set(const Uid &u, const ID i);
    void set(const Uid &u, const Key &k);
    void set(const Uid &u, const AText &n);
    void set(const Uid::Type t);
    void set(const Uid::Type t, const ID i);
    void set(const Uid::Type t, const Key &k);
    void set(const Uid::Type t, const AText &n);
    void set(const ID i);
    void set(const Key &k);
    void set(const AText &n);
    void set(const Uid &u, const ID i, const Key &k, const AText &n);
    void set(const Uid::Type t, const ID i, const Key &k, const AText &n);

private:
    static QWORD smCtorSeq;
};

extern EIRTYPE_EXPORT QDebug operator << (QDebug debug, const Ident &ident);
