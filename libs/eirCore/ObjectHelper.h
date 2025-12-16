#pragma once
#include "eirCore.h"

#include <QObject>

#include <QString>
#include <QStringList>

#include <CText.h>
#include <KeyMap.h>

class EIRCORE_EXPORT ObjectHelper
{
public: // types
    typedef KeyMapT<CText, QMetaProperty> NameMetaPropertyMap;

public: // ctors
    ObjectHelper(QObject *obj);

public: // const
    const QMetaObject * metaObject() const;
    const QMetaEnum metaEnum(const QString &enumName) const;
    QStringList namesOfEnums(const bool all=false) const;
    QStringList keysInEnum(const QString &enumName) const;
    bool enumIsFlags(const QString &enumName) const;
    QString enumKey(const QString &enumName, const int value) const;
    int enumValue(const QString &enumName, const QString &key) const;
    QStringList flagKeys(const QString &enumName, int flags,
                         const bool isSet=true) const;
    bool isValidPropertyName(const CText &name, const bool okDynamic=true) const;
    bool isValidEnumName(const CText &enumName) const;
    bool isValidEnumKey(const CText &enumName, const CText &key) const;

public: // non-const
    bool setEnum(const CText &enumName, const CText &enumKey);
    NameMetaPropertyMap readProperties(const bool readAll=false);
    void set(const KeySegMap values, const bool okDynamic=false);

public: // pointers
    QObject * obj();

private:
    QObject * mpObject=nullptr;
    NameMetaPropertyMap mNameMetaPropertyMap;
};

inline QObject *ObjectHelper::obj() { Q_CHECK_PTR(mpObject); return mpObject; }
