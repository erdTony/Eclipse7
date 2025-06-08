#include "ObjectHelper.h"

#include <QMetaEnum>
#include <QMetaObject>
#include <QString>
#include <QStringList>

ObjectHelper::ObjectHelper(const QObject *obj) : cmpObject(obj) {;}

const QMetaObject * ObjectHelper::metaObject() const
{
    const QMetaObject * result = nullptr;
    Q_CHECK_PTR(cmpObject);
    result = cmpObject->metaObject();
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

