#include "ObjdetCatalog.h"

#include "ObjdetCatalogItem.h"
#include "ObjectHelper.h"

ObjdetCatalog::ObjdetCatalog(const QString &catXmlFileName, QObject *parent)
    : QObject(parent)
    , mCatFileInfo(QFileInfo(catXmlFileName))
{
    QString result;
    result = readXmlFile();
    if ( ! result.isEmpty())
        qCritical() << result;
}

bool ObjdetCatalog::fileExists() const
{
    return mCatFileInfo.exists();
}

ObjdetCatalogItem ObjdetCatalog::item(const ObjdetCatalogItem::Key &key) const
{
    return mKeyItemMap.value(key);
}

QString ObjdetCatalog::readXmlFile()
{
    if ( ! fileExists() )
        return "Catalog XmlFile doesn't exist";                     /*=====*/
    QFile * pFile = new QFile(fileInfo().absoluteFilePath(), this);
    if ( ! pFile->open(QIODevice::ReadOnly | QIODevice::Text))
        return "Unable to open Catalog XmlFile";                    /*=====*/
    const QByteArray cBytes = pFile->readAll();
    pFile->close();
    pFile->deleteLater();
    pFile = nullptr;
    QDomDocument tDoc("Catalog");
    if ( ! tDoc.setContent(cBytes))
        return "Invalid Catalog XmlFile document";                  /*=====*/
    qDebug() << Q_FUNC_INFO << tDoc.toString(2);
    const QDomElement cRoot = tDoc.documentElement();
    const QDomNodeList cClassNodes = cRoot.elementsByTagName("DetectorClass");
    for (int ix = 0; ix < cClassNodes.length(); ++ix)
    {
        const QDomNode cClassNode = cClassNodes.item(ix);
        if (cClassNode.isElement())
        {
            const QDomElement cClassDE = cClassNode.toElement();
            processClassDE(cClassDE);
        }
    }
    if (cRoot.isNull())
        return "Catalog Xml is Null";                               /*=====*/
    foreach (const QString s, toDebugStrings()) qDebug() << s;
    return QString();
}

QString ObjdetCatalog::processClassDE(const QDomElement &classDE)
{
    QString result;
    const QDomNodeList cDetectorNodes = classDE.elementsByTagName("Detector");
    qDebug() << Q_FUNC_INFO << classDE.attribute("Name")
             <<  cDetectorNodes.length();
    for (int ix = 0; ix < cDetectorNodes.length(); ++ix)
    {
        const QDomNode cDetectorNode = cDetectorNodes.item(ix);
        if (cDetectorNode.isElement())
        {
            const QDomElement cDetectorDE = cDetectorNode.toElement();
            extractDetectorItems(classDE, cDetectorDE);
        }
    }
    if (mClassElementMap.isEmpty())
        result = "No Classes in Catalog XmlFile";
    return result;
}

QString ObjdetCatalog::extractDetectorItems(const QDomElement &classDE,
                                            const QDomElement &detectorDE)
{
    qDebug() << Q_FUNC_INFO << classDE.attribute("Name")
             << detectorDE.attribute("Name");
    QString result;
    const QString cClassName = classDE.attribute("Name");
    const Objdet::Class cClass = Objdet::objectClass(cClassName);
    if ( ! mClassElementMap.contains(cClass))
    {
        const QString cClassDefault = classDE.attribute("Default");
        mClassElementMap.insert(cClass, classDE);
        mClassDefaultDetectorMap.insert(cClass, cClassDefault);
    }

    const QString cDetectorName = detectorDE.attribute("Name");
    const QString cDetectorWidth = detectorDE.attribute("Width");
    const QString cDetectorHeight = detectorDE.attribute("Height");
    ObjdetCatalogItem tItem(cDetectorName, cClass);
    const QSize cDetectorSize(cDetectorWidth.toInt(),
                              cDetectorHeight.toInt());
    tItem.catalogSize(cDetectorSize);
    mKeyItemMap.insert(tItem.key(), tItem);
    return result;
}

QStringList ObjdetCatalog::toDebugStrings()
{
    QStringList result;
    // TODO mClassElementMap
    // TODO mClassDefaultDetectorMap
    foreach (const ObjdetCatalogItem::Key cKey, mKeyItemMap.keys())
    {
        const ObjdetCatalogItem cOCI = item(cKey);
        const QString cItemString = QString("%1:%2 = %3,%4 %5")
            .arg(cKey.first).arg(cKey.second)
            .arg(cOCI.catalogSize().width())
            .arg(cOCI.catalogSize().height())
            .arg(cOCI.xmlFileName());
        result << cItemString;
    }
    return result;
}

bool operator < (const ObjdetCatalogItem::Key &lhs,
                 const ObjdetCatalogItem::Key &rhs)
{
    if (lhs.first  < rhs.first)  return true;
    if (lhs.second < rhs.second) return true;
    return false;
}
