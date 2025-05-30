#include "ObjdetCatalogItem.h"

#include <QFileInfo>
#include <QSize>

//#include "ObjdetCatalog.h"

class ObjdetCatalogItemData : public QSharedData
{
public:
    Objdet::Class           dClass;
    QString                 dDetectorName;
    QString                 dDescription;
    QString                 dXmlFileName;
    QFileInfo               dXmlFileInfo;
    QSize                   dCatalogSize;
    cv::CascadeClassifier * dpCascade;
    QSize                   dCascadeSize;
};


ObjdetCatalogItem::ObjdetCatalogItem(const Objdet::Class cls)
    : data(new ObjdetCatalogItemData)
{
    oclass(cls);
}

ObjdetCatalogItem::ObjdetCatalogItem(const QString &dname, const Objdet::Class cls)
    : data(new ObjdetCatalogItemData)
{
    detectorName(dname), oclass(cls);
}

QString ObjdetCatalogItem::className() const
{
    Q_ASSERT(data);
    return Objdet::className(data->dClass);
}

QString ObjdetCatalogItem::detectorName() const
{
    Q_ASSERT(data);
    return data->dDetectorName;
}

QString ObjdetCatalogItem::xmlFileName() const
{
    return xmlFileInfo().filePath();
}

QFileInfo ObjdetCatalogItem::xmlFileInfo() const
{
    Q_ASSERT(data);
    return data->dXmlFileInfo;
}

bool ObjdetCatalogItem::xmlFileExists() const
{
    return xmlFileInfo().exists();
}

QSize ObjdetCatalogItem::catalogSize() const
{
    Q_ASSERT(data);
    return data->dCatalogSize;
}

ObjdetCatalogItem::Key ObjdetCatalogItem::key() const
{
    return Key(className(), detectorName());
}

bool ObjdetCatalogItem::read(const QDomElement &itemDE)
{
    bool result=true;
    result &= itemDE.hasAttribute("Name");
    result &= itemDE.hasAttribute("Description");
    result &= itemDE.hasAttribute("Width");
    result &= itemDE.hasAttribute("Height");
    result &= itemDE.hasAttribute("XmlFile");
    if ( ! result) return result;

    const QString cName = itemDE.attribute("Name");
    const QString cDesc = itemDE.attribute("Description");
    const QString cWidth = itemDE.attribute("Width");
    const QString cHeight = itemDE.attribute("Height");
    const QString cXmlFileName = itemDE.attribute("XmlFile");

    detectorName(cName);
    description(cDesc);
    xmlFile(cXmlFileName);
    catalogSize(QSize(cWidth.toInt(), cHeight.toInt()));
    result &= ! xmlFileExists();
    result &= ! catalogSize().isEmpty();

    return result;
}

void ObjdetCatalogItem::detectorName(const QString &dnm)
{
    Q_ASSERT(data);
    data->dDetectorName = dnm;
}

void ObjdetCatalogItem::description(const QString &desc)
{
    Q_ASSERT(data);
    data->dDescription = desc;
}

void ObjdetCatalogItem::oclass(const Objdet::Class cls)
{
    Q_ASSERT(data);
    data->dClass = cls;
}

void ObjdetCatalogItem::xmlFile(const QString &fileName)
{
    Q_ASSERT(data);
    data->dXmlFileName = fileName;
    data->dXmlFileInfo = QFileInfo(fileName);
}

void ObjdetCatalogItem::xmlFile(const QFileInfo &fi)
{
    Q_ASSERT(data);
    data->dXmlFileInfo = fi;
    data->dXmlFileName = data->dXmlFileInfo.filePath();
}

void ObjdetCatalogItem::catalogSize(const QSize &sz)
{
    Q_ASSERT(data);
    data->dCatalogSize = sz;
}

// --------------------- QSharedData ----------------------
ObjdetCatalogItem::ObjdetCatalogItem() : data(new ObjdetCatalogItemData) {;}
ObjdetCatalogItem::ObjdetCatalogItem(const ObjdetCatalogItem &rhs) : data{rhs.data} {;}
ObjdetCatalogItem::~ObjdetCatalogItem() {;}
ObjdetCatalogItem &ObjdetCatalogItem::operator=(const ObjdetCatalogItem &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

