#include "ObjectHelper.h"

#include <QMetaEnum>
#include <QMetaObject>
#include <QString>
#include <QStringList>

#include <KeySeg.h>
#include <Types.h>

ObjectHelper::ObjectHelper(QObject *obj) : mpObject(obj) {;}

const QMetaObject * ObjectHelper::metaObject() const
{
    const QMetaObject * result = nullptr;
    Q_CHECK_PTR(mpObject);
    result = mpObject->metaObject();
    Q_CHECK_PTR(result);
    return result;
}

const QMetaEnum ObjectHelper::metaEnum(const QString &enumName) const
{
    QMetaEnum result;
    const QMetaObject * pMetaObject = metaObject();
    const int cEnumIndex = pMetaObject->indexOfEnumerator(qPrintable(enumName));
    if (cEnumIndex >= 0)
        result = pMetaObject->enumerator(cEnumIndex);
    return result;
}

QStringList ObjectHelper::namesOfEnums(const bool all) const
{
    QStringList result;
    const QMetaObject * pMetaObject = metaObject();
    const unsigned cEnumCount = pMetaObject->enumeratorCount();
    const unsigned cEnumBase = all ? 0 : pMetaObject->enumeratorOffset();
    for (unsigned ix = cEnumBase; ix < cEnumCount; ++ix)
        result << pMetaObject->enumerator(ix).name();
    return result;
}

QStringList ObjectHelper::keysInEnum(const QString &enumName) const
{
    QStringList result;
#ifdef QT_DEBUG
    Q_ASSERT(namesOfEnums().contains(enumName));
#endif
    const QMetaEnum cMetaEnum = metaEnum(enumName);
    if (cMetaEnum.isValid())
    {
        const unsigned cKeyCount = cMetaEnum.keyCount();
        for (unsigned ix = 0; ix < cKeyCount; ++ix)
            result << cMetaEnum.key(ix);
    }
    return result;
}

bool ObjectHelper::enumIsFlags(const QString &enumName) const
{
    bool result = false;
    const QMetaEnum cMetaEnum = metaEnum(enumName);
    if (cMetaEnum.isValid() && cMetaEnum.isFlag()) result = true;
    return result;
}

QString ObjectHelper::enumKey(const QString &enumName, const int value) const
{
    QString result;
    const QMetaEnum cMetaEnum = metaEnum(enumName);
    if (cMetaEnum.isValid())
        result = cMetaEnum.valueToKey(value);
    return result;
}

int ObjectHelper::enumValue(const QString &enumName, const QString &key) const
{
    int result = -2;
    const QMetaEnum cMetaEnum = metaEnum(enumName);
    if (cMetaEnum.isValid())
        result = cMetaEnum.keyToValue(qPrintable(key));
    return result;
}

QStringList ObjectHelper::flagKeys(const QString &enumName, int flags, const bool isSet) const
{
    qInfo() << Q_FUNC_INFO << enumName << Qt::hex << flags << isSet;
    QStringList result;
    const QMetaEnum cMetaEnum = metaEnum(enumName);
    qDebug() << cMetaEnum.enumName()
             << (cMetaEnum.isFlag() ? "isFlag" : "NOTflag")
             << (cMetaEnum.isValid() ? "isValid" : "NOTvalid");
    if (cMetaEnum.isValid())
    {
        if ( ! isSet) flags = ~ flags;
        QString tKeys = cMetaEnum.valueToKeys(flags);
        result = tKeys.split('|');
    }
#ifdef QT_DEBUG
    else
    {
        const QMetaType cMetaType = cMetaEnum.metaType();
        qDebug() << "Type" << cMetaType.id() << cMetaType.name() << cMetaType.flags();
    }
    qDebug() << Q_FUNC_INFO << "result" << result;
#endif
    return result;
}


bool ObjectHelper::isValidPropertyName(const KeySeg &name, const bool okDynamic) const
{
    return mNameMetaPropertyMap.contains(name)
                && (okDynamic || mNameMetaPropertyMap.value(name).isValid());
}

ObjectHelper::NameMetaPropertyMap ObjectHelper::readProperties(const bool readAll)
{
    NameMetaPropertyMap result;
    const QMetaObject * pMO = metaObject();
    const int cPropCount = pMO->propertyCount();
    for (Index ix = readAll ? 0 : pMO->propertyOffset();
         ix < (Index)cPropCount;
         ++ix)
    {
        const QMetaProperty cMP = pMO->property(ix);
        const KeySeg cName = cMP.name();
        result.insert(cName, cMP);
    }
    foreach (const QByteArray cBA, obj()->dynamicPropertyNames())
        result.insert(KeySeg(AText(cBA)), QMetaProperty());
    return mNameMetaPropertyMap = result;
}

void ObjectHelper::set(const KeySegMap values, const bool okDynamic)
{
    foreach (const KeySeg &name, values.keys())
    {
        if (okDynamic || isValidPropertyName(name))
        {
            const QVariant cVar = values.value(name);
            obj()->setProperty(name, cVar);
        }
    }
}

