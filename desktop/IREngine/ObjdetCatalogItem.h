#pragma once

#include <QSharedDataPointer>

#include <QDomElement>
#include <QFileInfo>
#include <QPair>
#include <QSize>
#include <QString>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include "Objdet.h"

class ObjdetCatalogItemData;

class ObjdetCatalogItem
{
public: // types
    typedef QPair<QString, QString> Key;

public: // Our ctors
    ObjdetCatalogItem(const Objdet::Class cls);
    ObjdetCatalogItem(const QString &dname, const Objdet::Class cls);

public: // const
    QString className() const;
    QString detectorName() const;
    QString xmlFileName() const;
    QFileInfo xmlFileInfo() const;
    bool xmlFileExists() const;
    QSize catalogSize() const;
    Key key() const;

public: // non-const
    bool read(const QDomElement &itemDE);
    void className(const QString &cnm);
    void detectorName(const QString &dnm);
    void description(const QString &desc);
    void oclass(const Objdet::Class cls);
    void xmlFile(const QString &fileName);
    void xmlFile(const QFileInfo &fi);
    void catalogSize(const QSize &sz);

    // --------------------- QSharedData ----------------------
public:
    ObjdetCatalogItem();
    ObjdetCatalogItem(const ObjdetCatalogItem &);
    ObjdetCatalogItem &operator=(const ObjdetCatalogItem &);
    ~ObjdetCatalogItem();
private:
    QSharedDataPointer<ObjdetCatalogItemData> data;
};


